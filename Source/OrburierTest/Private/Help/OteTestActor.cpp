// Fill out your copyright notice in the Description page of Project Settings.


#include "OteTestActor.h"
#include "OteOpenOrbSystemComponent.h"
#include "OteTestComponent1.h"
#include "OteTestComponent2.h"
#include "Attributes/OteTestInputAttributeContainer.h"

// Sets default values
AOteTestActor::AOteTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OrbSystemComponent = CreateDefaultSubobject<UOteOpenOrbSystemComponent>("OrbSystemComponent");
	OteTestComponent1 = CreateDefaultSubobject<UOteTestComponent1>("OteTestComponent1");
	OteTestComponent2 = CreateDefaultSubobject<UOteTestComponent2>("OteTestComponent2");
}

// Called when the game starts or when spawned
void AOteTestActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AOteTestActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AOteTestActor::OnOrburierSetup_Implementation(FOrbParticipantSetupContext& context)
{
	context.AddInputAttributeContainer<FOteTestInputAttributeContainer1>();
	context.AddSyncAttributeContainer<FOteTestSyncAttributeContainer1>();
	context.AddAuxAttributeContainer<FOteTestAuxAttributeContainer1>();

	return true;
}

