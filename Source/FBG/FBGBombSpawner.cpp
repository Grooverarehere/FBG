// Fill out your copyright notice in the Description page of Project Settings.


#include "FBGBombSpawner.h"

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
	UE_LOG(LogTemp, Warning, TEXT("Actor: %s"),*OwnerSpawner->GetFName().ToString());
	UE_LOG(LogTemp, Warning, TEXT("BlastLength: %f"), BlastLength);
}

