// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "FBGBombSpawner.h"
#include "FBGBomb.generated.h"

UCLASS()
class FBG_API AFBGBomb : public AActor
{
	GENERATED_BODY()
	
		UPROPERTY()
		class USceneComponent* SceneRoot;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;
	UPROPERTY(EditAnywhere)
		class UNiagaraComponent* Fuse_Particle;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BombCollision;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UBoxComponent* BombOverlapCollision;
	UPROPERTY(EditDefaultsOnly, Category = Bomb)
		TSubclassOf<class AFBGBombBlast> BombBlastClass;
public:	
	// Sets default values for this actor's properties
	AFBGBomb();



	void IgniteBomb(AFBGBombSpawner* Spawner, float BlastLenght, AActor* Owner);
protected:
	TArray<AActor*>ActorToIgnore;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetCollisionsToActorsToIgnore();

	 UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
