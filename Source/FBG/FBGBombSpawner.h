// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FBGBombSpawner.generated.h"

UCLASS()
class FBG_API AFBGBombSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFBGBombSpawner();

	UPROPERTY(VisibleAnywhere)
		bool bIsOccupied;
	UPROPERTY(EditDefaultsOnly, Category = Bomb)
		TSubclassOf<class AFBGBomb> BombClass;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION()
		void SpawnBomb(AActor*OwnerSpawner,float BlastLength);
};
