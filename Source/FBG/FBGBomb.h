// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Components/BoxComponent.h"
#include "FBGBombSpawner.h"
#include "IDamage.h"
#include "Components/TimelineComponent.h"
#include "Components/AudioComponent.h"
#include "Sound/SoundBase.h"
#include "FBGBomb.generated.h"

UCLASS()
class FBG_API AFBGBomb : public AActor, public IIDamage
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
	UPROPERTY(EditAnywhere)
		UCurveFloat* EmissiveCurve;
	UPROPERTY(EditAnywhere)
		UCurveFloat* BombSizeCurve;
	UPROPERTY(EditDefaultsOnly, Category = Bomb)
		 USoundBase* SparklerClass;
	UPROPERTY(EditDefaultsOnly, Category = Bomb)
		USoundBase* ExplosionClass;
public:	
	// Sets default values for this actor's properties
	AFBGBomb();

	void IgniteBomb(AFBGBombSpawner* Spawner, float BlastLength, AActor* Owner);

	virtual void Damage() override;
protected:
	TArray<AActor*>ActorToIgnore;
	TArray<AFBGBombBlast*>SpawnedBlast;
	AFBGBombSpawner* ActorSpawner;
	float m_BlastLength;
	AActor* BombOwner;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UTimelineComponent* ExplodeTimeLine;
	FOnTimelineFloat UpdateEmissiveFloat;
	FOnTimelineFloat UpdateBombsizeFloat;
	FOnTimelineEventStatic FinishedFunctionFloat;
	FTimerHandle ExplodeTimer;
	bool bExplode;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UAudioComponent* ActiveSound;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void SetCollisionsToActorsToIgnore();

	 UFUNCTION()
		void OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	 void SpawnBlast();
	 UFUNCTION()
	 void EmisiveUpdate(float Output);
	 UFUNCTION()
	 void BombSizeUpdate(float Output);
	 UFUNCTION()
		 void FinishedTimelineFunction();
	 UFUNCTION()
		 void Explode();
	
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
