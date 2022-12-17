// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "MyTestStruct.generated.h"

/**
 * 
 */
USTRUCT()
struct ORBURIERTEST_API FMyTestStruct
{
	GENERATED_BODY()
public:
	FMyTestStruct()
	{
		BoolValue = false;
		FloatValue = 0.f;
	}

	UPROPERTY()
	bool BoolValue;
	
	UPROPERTY()
	float FloatValue;
};
