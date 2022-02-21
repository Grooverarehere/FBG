// Fill out your copyright notice in the Description page of Project Settings.


#include "FBGItemSpeedDown.h"
#include "FBGCharacter.h"

AFBGItemSpeedDown::AFBGItemSpeedDown()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>staticmesh(TEXT("'/Game/BomberGuys/Assets/3D_Assets/Meshes/Items/SpeedDown.SpeedDown'"));
	if (staticmesh.Succeeded())
	{
		Mesh->SetStaticMesh(staticmesh.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>arrowmesh(TEXT("'/Game/BomberGuys/Assets/3D_Assets/Meshes/Items/ArrowDown.ArrowDown'"));
	if (arrowmesh.Succeeded())
	{
		Mesh_Arrow->SetStaticMesh(arrowmesh.Object);
	}
}

void AFBGItemSpeedDown::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFBGItemSpeedDown::OnOverlapBegin);
}

void AFBGItemSpeedDown::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFBGCharacter* character = Cast<AFBGCharacter>(OtherActor);
	if (character)
	{
		character->PlayItemSound();
		if (character->Speed > 1)
		{
			character->Speed--;
			character->ChangeSpeed();
		}
		Destroy();
	}
}
