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

}

