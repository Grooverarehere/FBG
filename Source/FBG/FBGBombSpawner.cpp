// Fill out your copyright notice in the Description page of Project Settings.


#include "FBGBombSpawner.h"
#include "FBGBomb.h"

// Sets default values
AFBGBombSpawner::AFBGBombSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AFBGBombSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AFBGBombSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFBGBombSpawner::SpawnBomb(AActor* OwnerSpawner, float BlastLength)
{
	
	FActorSpawnParameters SpawnParams;
	SpawnParams.Owner = OwnerSpawner;
	SpawnParams.Instigator = GetInstigator();
	AFBGBomb * bomb=GetWorld()->SpawnActor<AFBGBomb>(BombClass, GetActorLocation(), GetActorRotation(), SpawnParams);
	bomb->IgniteBomb(this, BlastLength, OwnerSpawner);
}

