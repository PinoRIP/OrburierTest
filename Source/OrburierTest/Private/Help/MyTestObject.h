// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/OrbActionHandle.h"
#include "UObject/Object.h"
#include "MyTestObject.generated.h"

/**
 * 
 */
UCLASS()
class ORBURIERTEST_API UMyTestObject : public UObject
{
	GENERATED_BODY()

public:
	FOrbActionHandle Handle;

	UFUNCTION()
	void SetHandle(FOrbActionHandle handle)
	{
		Handle = handle;
	}
};
