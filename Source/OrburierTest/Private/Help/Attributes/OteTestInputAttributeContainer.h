// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Attributes/OrbAttributeContainer.h"
#include "UObject/Object.h"
#include "OteTestInputAttributeContainer.generated.h"

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestInputAttributeContainer1 : public FOrbInputAttributeContainer
{
	GENERATED_BODY()

public:
 UPROPERTY()
 int32 A = 0;

 UPROPERTY()
 int32 B = 0;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestInputAttributeContainer1_1 : public FOteTestInputAttributeContainer1
{
 GENERATED_BODY()

public:
 UPROPERTY()
 int32 C = 0;

 UPROPERTY()
 int32 D = 0;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestInputAttributeContainer2 : public FOrbInputAttributeContainer
{
 GENERATED_BODY()
 
public:
 UPROPERTY()
 int32 E = 0;
 UPROPERTY()
 int32 F = 0;
 UPROPERTY()
 FVector G = FVector(0, 0, 0);
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestSyncAttributeContainer1 : public FOrbSyncAttributeContainer
{
	GENERATED_BODY()

public:
 UPROPERTY()
 FRotator S = FRotator(0, 0, 0);
 UPROPERTY()
 FVector Y = FVector(0, 0, 0);
 UPROPERTY()
 int64 N = 0;
 UPROPERTY()
 float C = 0;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestSyncAttributeContainer1_1 : public FOteTestSyncAttributeContainer1
{
 GENERATED_BODY()
 
public:
 UPROPERTY()
 int32 No2 = 0;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestSyncAttributeContainer2 : public FOrbSyncAttributeContainer
{
 GENERATED_BODY()

public:
 UPROPERTY()
 FRotator S = FRotator(0, 0, 0);
 UPROPERTY()
 FVector Y = FVector(0, 0, 0);
 UPROPERTY()
 int64 N = 0;
 UPROPERTY()
 float C = 0;
 UPROPERTY()
 double N0 = 0;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestAuxAttributeContainer1 : public FOrbAuxAttributeContainer
{
 GENERATED_BODY()

public:
 UPROPERTY()
 FRotator A = FRotator(0, 0, 0);
 UPROPERTY()
 FVector U = FVector(0, 0, 0);
 UPROPERTY()
 int64 X = 0;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestAuxAttributeContainer1_1 : public FOteTestAuxAttributeContainer1
{
 GENERATED_BODY()
 
public:
 UPROPERTY()
 FRotator A2 = FRotator(0, 0, 0);
 UPROPERTY()
 FVector U2 = FVector(0, 0, 0);
 UPROPERTY()
 int64 X2 = 0;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestAuxAttributeContainer2 : public FOrbAuxAttributeContainer
{
 GENERATED_BODY()

public:
 UPROPERTY()
 int32 A = 0;
 UPROPERTY()
 int32 B = 0;
};

