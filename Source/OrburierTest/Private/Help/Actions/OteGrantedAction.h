// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/OrbAction.h"
#include "UObject/Object.h"
#include "OteGrantedAction.generated.h"

/**
 * 
 */
UCLASS()
class ORBURIERTEST_API UOteGrantedAction : public UOrbAction
{
	GENERATED_BODY()
	
public:
	virtual EOrbAvailabilityPolicy GetAvailabilityPolicy() const override { return EOrbAvailabilityPolicy::Granted; }
};
