// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "IDamage.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UIDamage : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class FBG_API IIDamage
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION()
	virtual void Damage() = 0;
};
