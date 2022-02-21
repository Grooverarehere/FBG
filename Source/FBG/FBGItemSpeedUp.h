// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FBGItemBase.h"
#include "FBGItemSpeedUp.generated.h"

/**
 * 
 */
UCLASS()
class FBG_API AFBGItemSpeedUp : public AFBGItemBase
{
	GENERATED_BODY()
	
public:
	AFBGItemSpeedUp();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
private:

	UFUNCTION()
		void OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
