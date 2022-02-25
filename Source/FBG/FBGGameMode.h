// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Blueprint/UserWidget.h"
#include "FBGCharacter.h"
#include "FBGGameMode.generated.h"

UCLASS(minimalapi)
class AFBGGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	AFBGGameMode();

	UFUNCTION(BlueprintCallable)
		void StartGame(int Level);
		void EndGame();
	UFUNCTION(BlueprintCallable)
		int GetEnemiesDefeat();
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int Seconds;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		int Minutes;
	UPROPERTY(EditAnywhere, Category = "Class Types")
		TSubclassOf<UUserWidget> WidgetEndClass;
	UPROPERTY(VisibleInstanceOnly, Category = "RunTime")
		class UUserWidget* EndInterface;
	UPROPERTY(EditAnywhere, Category = "Class Types")
		TSubclassOf<UUserWidget> WidgetClass;
	UPROPERTY(VisibleInstanceOnly, Category = "RunTime")
		class UUserWidget* UserInterface;
	FTimerHandle TimerHandle;
	TArray<FString> levels;
	
	UPROPERTY(EditAnywhere, Category = "Class Types")
		TSubclassOf<AFBGCharacter> NPCClass;
	TArray<AActor*>EnemiesArray;

	virtual void BeginPlay() override;
	void CountTime();
	virtual void Tick(float DeltaSeconds) override;
	
};



