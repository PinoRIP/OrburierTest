// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/OrbAction.h"
#include "UObject/Object.h"
#include "MyTestAction.generated.h"

/**
 * 
 */
UCLASS()
class ORBURIERTEST_API UMyTestAction : public UOrbAction
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS()
class ORBURIERTEST_API UMyPublicTestAction : public UOrbAction
{
	GENERATED_BODY()

public:
	EOrbAvailabilityPolicy GetAvailabilityPolicy() const override
	{
		return EOrbAvailabilityPolicy::Public;
	}
};