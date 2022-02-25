// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "IDamage.h"
#include "Components/TimelineComponent.h"
#include "NiagaraFunctionLibrary.h"
#include "Sound/SoundBase.h"
#include "FBGCharacter.generated.h"

UCLASS(Blueprintable)
class AFBGCharacter : public ACharacter, public IIDamage
{
	GENERATED_BODY()

public:
	AFBGCharacter();

	// Called every frame.
	virtual void Tick(float DeltaSeconds) override;

	/** Returns TopDownCameraComponent subobject **/
	FORCEINLINE class UCameraComponent* GetTopDownCameraComponent() const { return TopDownCameraComponent; }
	/** Returns CameraBoom subobject **/
	FORCEINLINE class USpringArmComponent* GetCameraBoom() const { return CameraBoom; }
	UPROPERTY(EditAnywhere)
		float BombSpawnerDistance;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int m_AmountOfBombs;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		bool bDied;
	UPROPERTY(EditAnywhere)
		UCurveFloat* EmissiveCurve;
	UPROPERTY(EditAnywhere)
		UNiagaraSystem* Ploof;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AActor>Gravestone;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int Blast;
	UPROPERTY(EditAnywhere)
		USoundBase* ItemSound;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		int Speed;
	UFUNCTION(BlueprintCallable)
		bool SpawnBomb();

	virtual void Damage() override;

	void PlayItemSound();

	void ChangeSpeed();
		 
private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	
	UPROPERTY(VisibleAnywhere)
		int m_Blast;

	UPROPERTY(VisibleAnywhere)
		AActor* BombSpawnerRef;

	UPROPERTY(VisibleAnywhere)
		UTimelineComponent* EmissiveTimeLine;
	FOnTimelineFloat UpdateEmissiveFloat;
	FOnTimelineEventStatic FinishedFunctionFloat;
	FTimerHandle DiedTimer;
	bool bDead;
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UFUNCTION()
		void EmissiveUpdate(float Output);
	UFUNCTION()
		void FinishedTimelineFunction();
	UFUNCTION()
		void Died();
	UFUNCTION()
		void EndGame();

};

