// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "OrbSystemComponent.h"
#include "OrbSystemParticipant.h"
#include "GameFramework/Actor.h"
#include "OteTestActor.generated.h"

UCLASS()
class ORBURIERTEST_API AOteTestActor : public AActor, public IOrbSystemParticipant
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AOteTestActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY()
	class UOrbSystemComponent* OrbSystemComponent;

	UPROPERTY()
	class UOteTestComponent1* OteTestComponent1;

	UPROPERTY()
	class UOteTestComponent2* OteTestComponent2;

	virtual bool OnOrburierSetup_Implementation(FOrbParticipantSetupContext& context) override;
};
