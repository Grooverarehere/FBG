// Fill out your copyright notice in the Description page of Project Settings.


#include "FBGItemSpeedUp.h"
#include "FBGCharacter.h"

AFBGItemSpeedUp::AFBGItemSpeedUp()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>staticmesh(TEXT("'/Game/BomberGuys/Assets/3D_Assets/Meshes/Items/SpeedUp_Item.SpeedUp_Item'"));
	if (staticmesh.Succeeded())
	{
		Mesh->SetStaticMesh(staticmesh.Object);
	}
	static ConstructorHelpers::FObjectFinder<UStaticMesh>arrowmesh(TEXT("'/Game/BomberGuys/Assets/3D_Assets/Meshes/Items/ArrowUp.ArrowUp'"));
	if (arrowmesh.Succeeded())
	{
		Mesh_Arrow->SetStaticMesh(arrowmesh.Object);
	}
}

void AFBGItemSpeedUp::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFBGItemSpeedUp::OnOverlapBegin);
}

void AFBGItemSpeedUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFBGCharacter* character = Cast<AFBGCharacter>(OtherActor);
	if (character)
	{
		character->PlayItemSound();
		if (character->Speed < 5)
		{
			character->Speed++;
			character->ChangeSpeed();
		}
		Destroy();
	}
}
