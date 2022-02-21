// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IDamage.h"
#include "FBGItemBombDown.h"
#include "FBGItemBombUp.h"
#include "FBGItemSpeedDown.h"
#include "FBGItemSpeedUp.h"
#include "FBGItemBlastDown.h"
#include "FBGItemBlastUp.h"
#include "FBGDestructible.generated.h"

UCLASS()
class FBG_API AFBGDestructible : public AActor, public IIDamage
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFBGDestructible();
	 
	UPROPERTY()
		class USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;
	UPROPERTY(EditDefaultsOnly, Category = Bomb)
		TSubclassOf<class AFBGBombSpawner> BombSpawnerClass;
	UPROPERTY(EditAnywhere)
		int PossibilityOfItem;
	UPROPERTY(EditAnywhere)
		int PossibilityOfGoodItem;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AFBGItemBombUp> ItemBomb1;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AFBGItemBombDown> ItemBomb2;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AFBGItemBlastUp> ItemBlast1;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AFBGItemBlastDown> ItemBlast2;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AFBGItemSpeedUp> ItemSpeed1;
	UPROPERTY(EditDefaultsOnly)
		TSubclassOf<class AFBGItemSpeedDown> ItemSpeed2;
	virtual void Damage() override;
protected:
	FTransform InitTransform;
	FTimerHandle DestructionTimer;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SpawnItem();

	void SpawnBombItem();
	void SpawnBlastItem();
	void SpawnSpeedItem();

	void Destruction();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
