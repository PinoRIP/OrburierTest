﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "OteTestComponent1.h"


// Sets default values for this component's properties
UOteTestComponent1::UOteTestComponent1()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UOteTestComponent1::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UOteTestComponent1::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

