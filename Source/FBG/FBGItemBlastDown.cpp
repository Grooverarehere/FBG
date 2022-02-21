// Fill out your copyright notice in the Description page of Project Settings.


#include "FBGItemBlastDown.h"
#include "FBGCharacter.h"

AFBGItemBlastDown::AFBGItemBlastDown()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>staticmesh(TEXT("'/Game/BomberGuys/Assets/3D_Assets/Meshes/Items/FireDown_Item.FireDown_Item'"));
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

void AFBGItemBlastDown::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFBGItemBlastDown::OnOverlapBegin);
}

void AFBGItemBlastDown::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFBGCharacter* character = Cast<AFBGCharacter>(OtherActor);
	if (character)
	{
		character->PlayItemSound();
		if (character->Blast > 1)
		{
			character->Blast--;
		}
		Destroy();
	}
}
