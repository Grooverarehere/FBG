// Copyright Epic Games, Inc. All Rights Reserved.

#include "FBGGameMode.h"
#include "FBGPlayerController.h"
#include "Kismet/GameplayStatics.h"
#include "UObject/ConstructorHelpers.h"

AFBGGameMode::AFBGGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
	// use our custom PlayerController class
	PlayerControllerClass = AFBGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget>EndWidgetClass(TEXT("'/Game/BomberGuys/Widgets/Gameplay/IntermissionScreen_WB'"));
	if (EndWidgetClass.Succeeded())
	{
		WidgetEndClass = EndWidgetClass.Class;
	}

	static ConstructorHelpers::FClassFinder<UUserWidget>InGameWidgetClass(TEXT("'/Game/BomberGuys/Widgets/Gameplay/Gameplay_HUD_WB'"));
	if (InGameWidgetClass.Succeeded())
	{
		WidgetClass = InGameWidgetClass.Class;
	}

	static ConstructorHelpers::FClassFinder<AFBGCharacter>Enemis(TEXT("'/Game/TopDownCPP/AI/NPC/BP_NPC'"));
	if (Enemis.Succeeded())
	{
		NPCClass = Enemis.Class;
	}

	levels.Add("Level01");
	levels.Add("Level02");
	levels.Add("Level03");
	levels.Add("Level04");
	levels.Add("Level05");
	levels.Add("Level06");
}

void AFBGGameMode::StartGame(int Level)
{
	if (Level == -1)
	{
		Level = FMath::RandRange(0, 17);

	}
	UGameplayStatics::OpenLevel(GetWorld(), *levels[Level]);
}

void AFBGGameMode::EndGame()
{
	if (WidgetEndClass->IsValidLowLevel())
	{
		EndInterface = CreateWidget(GetWorld(), WidgetEndClass);
		if (EndInterface != nullptr)
		{
			EndInterface->AddToViewport();
			AFBGPlayerController* controller = Cast<AFBGPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			controller->SetPause(true);
			controller->SetShowMouseCursor(true);
			controller->SetInputMode(FInputModeUIOnly());
		}
	}
}

int AFBGGameMode::GetEnemiesDefeat()
{
	int enemiesDefeat = 0;
	switch (EnemiesArray.Num())
	{
	case 0:
		enemiesDefeat = 3;
		break;
	case 1:
		enemiesDefeat = 2;
		break;
	case 2:
		enemiesDefeat = 1;
		break;
	case 3:
		enemiesDefeat = 0;
		break;
	}

	return enemiesDefeat;
}

void AFBGGameMode::BeginPlay()
{
	Minutes = 0;
	Seconds = 0;

	GetWorldTimerManager().SetTimer(TimerHandle, this, &AFBGGameMode::CountTime, 1.f, true);
	if (WidgetClass->IsValidLowLevel())
	{
		FString levelName = GetWorld()->GetMapName();
		if (GetWorld()->GetMapName() != "MainMenu_Level") {
			UserInterface = CreateWidget(GetWorld(), WidgetClass);
			if (UserInterface != nullptr)
			{
				UserInterface->AddToViewport();
				AFBGPlayerController* controller = Cast<AFBGPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
				controller->SetShowMouseCursor(false);
				controller->SetInputMode(FInputModeGameOnly());
			}

		}
		else
		{
			AFBGPlayerController* controller = Cast<AFBGPlayerController>(UGameplayStatics::GetPlayerController(GetWorld(), 0));
			controller->SetShowMouseCursor(true);
			controller->SetInputMode(FInputModeUIOnly());
		}
	}
}

void AFBGGameMode::CountTime()
{
	if (Seconds < 59) {
		Seconds++;
	}
	else
	{
		Seconds = 0;
		Minutes++;
	}
}

void AFBGGameMode::Tick(float DeltaSeconds)
{
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), NPCClass, EnemiesArray);
	if (EnemiesArray.Num() < 1)
	{
		if (GetWorld()->GetMapName() != "MainMenu_Level") {
			EndGame();
		}
	}
}
