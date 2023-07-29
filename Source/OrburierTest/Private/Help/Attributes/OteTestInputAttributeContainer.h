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
 int32 A;
 int32 B;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestInputAttributeContainer1_1 : public FOteTestInputAttributeContainer1
{
 GENERATED_BODY()

public:
 int32 C;
 int32 D;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestInputAttributeContainer2 : public FOrbInputAttributeContainer
{
 GENERATED_BODY()
 
public:
 int32 E;
 int32 F;
 FVector G;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestSyncAttributeContainer1 : public FOrbSyncAttributeContainer
{
	GENERATED_BODY()

public:
 FRotator S;
 FVector Y;
 int64 N;
 float C;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestSyncAttributeContainer1_1 : public FOteTestSyncAttributeContainer1
{
 GENERATED_BODY()
 
public:
 int32 No2;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestSyncAttributeContainer2 : public FOrbSyncAttributeContainer
{
 GENERATED_BODY()

public:
 FRotator S;
 FVector Y;
 int64 N;
 float C;
 double N0;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestAuxAttributeContainer1 : public FOrbAuxAttributeContainer
{
 GENERATED_BODY()

public:
 FRotator A;
 FVector U;
 int64 X;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestAuxAttributeContainer1_1 : public FOteTestAuxAttributeContainer1
{
 GENERATED_BODY()
 
public:
 FRotator A2;
 FVector U2;
 int64 X2;
};

USTRUCT(BlueprintType)
struct ORBURIERTEST_API FOteTestAuxAttributeContainer2 : public FOrbAuxAttributeContainer
{
 GENERATED_BODY()

public:
 int32 A;
 int32 B;
};

