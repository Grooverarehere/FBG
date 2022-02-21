// Fill out your copyright notice in the Description page of Project Settings.


#include "FBGDestructible.h"
#include "FBGBombSpawner.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AFBGDestructible::AFBGDestructible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("SceneRoot"));
	RootComponent = SceneRoot;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	PossibilityOfItem = 5;
	PossibilityOfGoodItem = 3;
}

void AFBGDestructible::Damage()
{
	InitTransform = UKismetMathLibrary::Conv_VectorToTransform(GetActorLocation());
	FActorSpawnParameters SpawnParams;
	GetWorld()->SpawnActor<AFBGBombSpawner>(BombSpawnerClass, InitTransform, SpawnParams);
	SpawnItem();
	GetWorldTimerManager().SetTimer(DestructionTimer, this, &AFBGDestructible::Destruction, 0.09f, false);
}

// Called when the game starts or when spawned
void AFBGDestructible::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFBGDestructible::SpawnItem()
{
	int r = UKismetMathLibrary::RandomIntegerInRange(0, PossibilityOfItem);
	FVector location = InitTransform.GetLocation();
	location.Z += 50.f;
	InitTransform = UKismetMathLibrary::Conv_VectorToTransform(location);
	switch (r)
	{
	case 0:
		SpawnBombItem();
		break;
	case 1:
		SpawnBlastItem();
		break;
	case 2:
		SpawnSpeedItem();
		break;
	default:
		UE_LOG(LogTemp, Warning, TEXT("Nada"));
		break;
	}
}

void AFBGDestructible::SpawnBombItem()
{
	int r = UKismetMathLibrary::RandomIntegerInRange(0, PossibilityOfGoodItem);
	switch (r)
	{
	case 0:
		GetWorld()->SpawnActor<AFBGItemBombUp>(ItemBomb1, InitTransform);
		break;
	case 1:
		GetWorld()->SpawnActor<AFBGItemBombUp>(ItemBomb1, InitTransform);
		break;
	case 2:
		GetWorld()->SpawnActor<AFBGItemBombDown>(ItemBomb2, InitTransform);
		break;
	default:
		break;
	}
}

void AFBGDestructible::SpawnBlastItem()
{
	int r = UKismetMathLibrary::RandomIntegerInRange(0, PossibilityOfGoodItem);
	switch (r)
	{
	case 0:
		GetWorld()->SpawnActor<AFBGItemBlastUp>(ItemBlast1, InitTransform);
		break;
	case 1:
		GetWorld()->SpawnActor<AFBGItemBlastUp>(ItemBlast1, InitTransform);
		break;
	case 2:
		GetWorld()->SpawnActor<AFBGItemBlastDown>(ItemBlast2, InitTransform);
		break;
	default:
		break;
	}
}

void AFBGDestructible::SpawnSpeedItem()
{
	int r = UKismetMathLibrary::RandomIntegerInRange(0, PossibilityOfGoodItem);
	switch (r)
	{
	case 0:
		GetWorld()->SpawnActor<AFBGItemSpeedUp>(ItemSpeed1, InitTransform);
		break;
	case 1:
		GetWorld()->SpawnActor<AFBGItemSpeedUp>(ItemSpeed1, InitTransform);
		break;
	case 2:
		GetWorld()->SpawnActor<AFBGItemSpeedDown>(ItemSpeed2, InitTransform);
		break;
	default:
		break;
	}
}

void AFBGDestructible::Destruction()
{
	Destroy();
}

// Called every frame
void AFBGDestructible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

