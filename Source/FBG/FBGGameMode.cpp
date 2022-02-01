// Copyright Epic Games, Inc. All Rights Reserved.

#include "FBGGameMode.h"
#include "FBGPlayerController.h"
#include "FBGCharacter.h"
#include "UObject/ConstructorHelpers.h"

AFBGGameMode::AFBGGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = AFBGPlayerController::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDownCPP/Blueprints/TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}