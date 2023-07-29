// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrbSystemParticipant.h"
#include "Components/ActorComponent.h"
#include "OteTestComponent2.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class ORBURIERTEST_API UOteTestComponent2 : public UActorComponent, public IOrbSystemParticipant
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UOteTestComponent2();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual bool OnOrburierSetup_Implementation(FOrbParticipantSetupContext& context) override;
};
