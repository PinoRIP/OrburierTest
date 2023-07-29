// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrbSystemComponent.h"
#include "Components/ActorComponent.h"
#include "OteOpenOrbSystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ORBURIERTEST_API UOteOpenOrbSystemComponent : public UOrbSystemComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOteOpenOrbSystemComponent();

	void CallConfigureParticipants();
	
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
