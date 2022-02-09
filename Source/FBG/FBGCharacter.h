// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "FBGCharacter.generated.h"

UCLASS(Blueprintable)
class AFBGCharacter : public ACharacter
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
	UFUNCTION()
		void SpawnBomb();

private:
	/** Top down camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* TopDownCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* CameraBoom;

	UPROPERTY(VisibleAnywhere)
		int m_AmountOfBombs;
	UPROPERTY(VisibleAnywhere)
		int m_Blast;

	UPROPERTY(VisibleAnywhere)
		AActor* BombSpawnerRef;
};

