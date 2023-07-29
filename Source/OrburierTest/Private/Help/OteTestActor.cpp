// Fill out your copyright notice in the Description page of Project Settings.


#include "OteTestActor.h"


// Sets default values
AOteTestActor::AOteTestActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	OrbSystemComponent = CreateDefaultSubobject<UOrbSystemComponent>("OrbSystemComponent");
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

