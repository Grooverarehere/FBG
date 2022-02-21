// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/SphereComponent.h"
#include "Components/TimelineComponent.h"
#include "FBGItemBase.generated.h"

UCLASS()
class FBG_API AFBGItemBase : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFBGItemBase();

	UPROPERTY()
		class USceneComponent* SceneRoot;
	UPROPERTY(VisibleDefaultsOnly, Category = Projectile)
		USphereComponent* CollisionComponent;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* Mesh_Arrow;
	UPROPERTY(EditAnywhere)
		UCurveFloat* RotationTimelineCurve;
	UPROPERTY(EditAnywhere)
		UCurveFloat* UpDownTimelineCurve;
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		UTimelineComponent* TimelineComponent;
	FOnTimelineFloat RotationFunctionFloat;
	FOnTimelineFloat UpDownFunctionFloat;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void RotationTimelineFunction(float Output);
	UFUNCTION()
		void UpDownTimelineFunction(float Output);

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
