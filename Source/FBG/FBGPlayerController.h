// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "FBGPlayerController.generated.h"

UCLASS()
class AFBGPlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	AFBGPlayerController();

	void StopInput();
protected:
	

	// Begin PlayerController interface
	virtual void PlayerTick(float DeltaTime) override;
	virtual void SetupInputComponent() override;
	// End PlayerController interface

	void Forward(float Value);
	void Right(float Value);
	void SpawnBomb();
};


