// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "NiagaraComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "FBGBombBlast.generated.h"

UCLASS()
class FBG_API AFBGBombBlast : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFBGBombBlast();

	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;
	UPROPERTY(EditAnywhere)
		class UNiagaraComponent* Blast_Particle;
	UPROPERTY(VisibleAnywhere, Category = Movement)
		UProjectileMovementComponent* ProjectileMovementComponent;

	void Initiate_BombBlast(float BlastLength);
protected:
	float m_BlastLength;
	FVector InitPosition;
	bool bCanMove;
	FTimerHandle BlastTimer;
	FTimerHandle StopBlastTimer;
	FTimerHandle DestroyTimer;
	bool bStop;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	
	void SetDamage();
	void StopBlast();
	void DestroyBlast();

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
