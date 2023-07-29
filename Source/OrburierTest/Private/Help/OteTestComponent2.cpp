// Fill out your copyright notice in the Description page of Project Settings.


#include "OteTestComponent2.h"

#include "Attributes/OteTestInputAttributeContainer.h"


// Sets default values for this component's properties
UOteTestComponent2::UOteTestComponent2()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOteTestComponent2::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOteTestComponent2::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

bool UOteTestComponent2::OnOrburierSetup_Implementation(FOrbParticipantSetupContext& context)
{
	context.AddSyncAttributeContainer<FOteTestSyncAttributeContainer1_1>();
	context.AddAuxAttributeContainer<FOteTestAuxAttributeContainer2>();

	return true;
}

