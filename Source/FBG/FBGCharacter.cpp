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
#include "FBGPlayerController.h"

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

	EmissiveTimeLine = CreateDefaultSubobject<UTimelineComponent>(TEXT("EmissiveTimeLine"));

	BombSpawnerDistance = 100.f;
	Blast = 2;
	m_AmountOfBombs = 1;
	Speed = 3;
}

void AFBGCharacter::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);

	
}

void AFBGCharacter::SpawnBomb()
{
	if (m_AmountOfBombs > 0)
	{
		BombSpawnerRef = nullptr;
		BombSpawnerDistance = 100.f;
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
					BombSpawner->SpawnBomb(this, UKismetMathLibrary::Conv_IntToFloat(Blast * 100));
				}
			}
		}
	}
}

void AFBGCharacter::Damage()
{
	if (!bDead)
	{
		bDead = true;
		
		
		AFBGPlayerController* cont = Cast<AFBGPlayerController>(GetController());
		cont->StopInput();
		bDied = true;
		GetWorldTimerManager().SetTimer(DiedTimer, this, &AFBGCharacter::Died, 1.2f, false);
			//Signal Game Over
			//Destroy();
		
		
		//delay y game over
	}
}

void AFBGCharacter::PlayItemSound()
{
	UGameplayStatics::PlaySound2D(GetWorld(),ItemSound);
}

void AFBGCharacter::ChangeSpeed()
{
	switch (Speed)
	{
	case 1:
		GetCharacterMovement()->MaxWalkSpeed = 350.f;
		break;
	case 2:
		GetCharacterMovement()->MaxWalkSpeed = 450.f;
		break;
	case 3:
		GetCharacterMovement()->MaxWalkSpeed = 550.f;
		break;
	case 4:
		GetCharacterMovement()->MaxWalkSpeed = 650.f;
		break;
	case 5:
		GetCharacterMovement()->MaxWalkSpeed = 750.f;
		break;
	}
}

void AFBGCharacter::BeginPlay()
{
	Super::BeginPlay();

	UpdateEmissiveFloat.BindDynamic(this, &AFBGCharacter::EmissiveUpdate);
	FinishedFunctionFloat.BindUFunction(this, "FinishedTimelineFunction");
	if (EmissiveTimeLine)
	{
		EmissiveTimeLine->AddInterpFloat(EmissiveCurve, UpdateEmissiveFloat);
		EmissiveTimeLine->SetTimelineFinishedFunc(FinishedFunctionFloat);
	}

}

void AFBGCharacter::EmissiveUpdate(float Output)
{
	GetMesh()->SetScalarParameterValueOnMaterials("Emissive", Output);
}

void AFBGCharacter::FinishedTimelineFunction()
{
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(GetWorld(), Ploof, GetActorLocation(), GetActorRotation());
	GetMesh()->SetVisibility(false);
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = this;
	SpawnParams.Instigator = GetInstigator();
	FVector loc=GetActorLocation();
	loc.Z -= 88.f;
	GetWorld()->SpawnActor<AActor>(Gravestone,loc, FRotator(0.f, 90.f, 0.f), SpawnParams);
}

void AFBGCharacter::Died()
{
	EmissiveTimeLine->PlayFromStart();
}
