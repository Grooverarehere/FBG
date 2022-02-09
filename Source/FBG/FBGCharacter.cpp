// Copyright Epic Games, Inc. All Rights Reserved.

#include "FBGCharacter.h"
#include "UObject/ConstructorHelpers.h"
#include "Camera/CameraComponent.h"
#include "Components/DecalComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/PlayerController.h"
#include "GameFramework/SpringArmComponent.h"
#include "HeadMountedDisplayFunctionLibrary.h"
#include "Materials/Material.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "FBGBombSpawner.h"
#include "Kismet/KismetMathLibrary.h"

AFBGCharacter::AFBGCharacter()
{
	// Set size for player capsule
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.0f);

	// Don't rotate character to camera direction
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	// Configure character movement
	GetCharacterMovement()->bOrientRotationToMovement = true; // Rotate character to moving direction
	GetCharacterMovement()->RotationRate = FRotator(0.f, 640.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	// Create a camera boom...
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->SetUsingAbsoluteRotation(true); // Don't want arm to rotate when character does
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));
	CameraBoom->bDoCollisionTest = false; // Don't want to pull camera in when it collides with level

	// Create a camera...
	TopDownCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("TopDownCamera"));
	TopDownCameraComponent->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	TopDownCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm


	// Activate ticking in order to update the cursor every frame.
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;

	BombSpawnerDistance = 100.f;
	m_Blast = 2;
}

void AFBGCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	
}

void AFBGCharacter::SpawnBomb()
{
	if (m_AmountOfBombs > 1)
	{
		BombSpawnerRef = nullptr;
		TArray<AActor*>SpawnersBomb;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AFBGBombSpawner::StaticClass(),SpawnersBomb);
		for (int i = 0; i < SpawnersBomb.Num(); i++) {
			if (FVector::Distance(SpawnersBomb[i]->GetActorLocation(), GetActorLocation()) <= BombSpawnerDistance)
			{
				BombSpawnerDistance = FVector::Distance(SpawnersBomb[i]->GetActorLocation(), GetActorLocation());
				BombSpawnerRef = SpawnersBomb[i];
			}
		}
		if (BombSpawnerRef->IsValidLowLevel())
		{
			AFBGBombSpawner* BombSpawner = Cast<AFBGBombSpawner>(BombSpawnerRef);
			if (BombSpawner->IsValidLowLevel())
			{
				if (!BombSpawner->bIsOccupied)
				{
					m_AmountOfBombs--;
					BombSpawner->SpawnBomb(this, UKismetMathLibrary::Conv_IntToFloat(m_Blast * 100));
				}
			}
		}
	}
}
