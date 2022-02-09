// Copyright Epic Games, Inc. All Rights Reserved.

#include "FBGPlayerController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "Runtime/Engine/Classes/Components/DecalComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "FBGCharacter.h"
#include "Engine/World.h"

AFBGPlayerController::AFBGPlayerController()
{
	
}

void AFBGPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);

	
}

void AFBGPlayerController::SetupInputComponent()
{
	// set up gameplay key bindings
	Super::SetupInputComponent();
	InputComponent->BindAxis("MoveForward", this, &AFBGPlayerController::Forward);
	InputComponent->BindAxis("MoveRight", this, &AFBGPlayerController::Right);
	InputComponent->BindAction("SpawnBomb", IE_Pressed, this, &AFBGPlayerController::SpawnBomb);
}

void AFBGPlayerController::Forward(float Value)
{
	const FVector direction(1.f, 0.f, 0.f);
	if (GetPawn())
		GetPawn()->AddMovementInput(direction, Value);
}

void AFBGPlayerController::Right(float Value)
{
	const FVector direction(0.f, 1.f, 0.f);
	if (GetPawn())
		GetPawn()->AddMovementInput(direction, Value);
}

void AFBGPlayerController::SpawnBomb()
{
	if (GetPawn())
	{
		AFBGCharacter* character = Cast<AFBGCharacter>(GetPawn());
		character->SpawnBomb();
	}
}

