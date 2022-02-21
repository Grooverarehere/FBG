// Fill out your copyright notice in the Description page of Project Settings.


#include "FBGItemBombDown.h"
#include "FBGCharacter.h"

AFBGItemBombDown::AFBGItemBombDown()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>staticmesh(TEXT("'/Game/BomberGuys/Assets/3D_Assets/Meshes/Items/Bomb_Item.Bomb_Item'"));
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

void AFBGItemBombDown::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFBGItemBombDown::OnOverlapBegin);
}

void AFBGItemBombDown::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFBGCharacter* character = Cast<AFBGCharacter>(OtherActor);
	if (character)
	{
		character->PlayItemSound();
		if (character->m_AmountOfBombs > 1)
		{
			character->m_AmountOfBombs--;
		}
		Destroy();
	}
}