// Fill out your copyright notice in the Description page of Project Settings.


#include "FBGItemBlastUp.h"
#include "FBGCharacter.h"

AFBGItemBlastUp::AFBGItemBlastUp()
{
	static ConstructorHelpers::FObjectFinder<UStaticMesh>staticmesh(TEXT("'/Game/BomberGuys/Assets/3D_Assets/Meshes/Items/FireUp_Item.FireUp_Item'"));
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

void AFBGItemBlastUp::BeginPlay()
{
	Super::BeginPlay();

	CollisionComponent->OnComponentBeginOverlap.AddDynamic(this, &AFBGItemBlastUp::OnOverlapBegin);
}

void AFBGItemBlastUp::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AFBGCharacter* character = Cast<AFBGCharacter>(OtherActor);
	if (character)
	{
		character->PlayItemSound();
		if (character->Blast < 10)
		{
			character->Blast++;
		}
		Destroy();
	}
}
