// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "MyTestStruct.h"
#include "UObject/Object.h"
#include "Utils/OrbStructReferencer.h"
#include "MyTestStructReferencer.generated.h"

/**
 * 
 */
UCLASS()
class UMyTestStructReferencer : public UOrbStructReferencer
{
	GENERATED_BODY()

public:
	virtual UScriptStruct* GetType() const override
	{
		return FMyTestStruct::StaticStruct();
	}
};
