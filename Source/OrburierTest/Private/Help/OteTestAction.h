// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Action/OrbAction.h"
#include "UObject/Object.h"
#include "OteTestAction.generated.h"

/**
 * 
 */
UCLASS()
class ORBURIERTEST_API UOteTestAction : public UOrbAction
{
	GENERATED_BODY()
};

/**
 * 
 */
UCLASS()
class ORBURIERTEST_API UOtePublicTestAction : public UOrbAction
{
	GENERATED_BODY()

public:
	EOrbAvailabilityPolicy GetAvailabilityPolicy() const override
	{
		return EOrbAvailabilityPolicy::Public;
	}

	virtual void Configure() override
	{
		Super::Configure();
		ConfigureInvoked++;
	}

	virtual bool CanActivate(const FOrbObserveContext& activationContext, const FOrbActionObserveContext& actionContext, bool isExternal) override
	{
		CanActivateInvoked++;
		return Super::CanActivate(activationContext, actionContext, isExternal);
	}

	virtual bool CanDeactivate(const FOrbObserveContext& deactivationContext, const FOrbActionObserveContext& actionContext, bool isExternal) override
	{
		CanDeactivateInvoked++;
		return Super::CanDeactivate(deactivationContext, actionContext, isExternal);
	}
	
	virtual void OnActivate(const FOrbExecutionContext& executionContext, const FOrbActionContext& actionContext) override
	{
		OnActivateInvoked++;
		Super::OnActivate(executionContext, actionContext);
	}

	virtual void OnDeactivate(const FOrbExecutionContext& executionContext, const FOrbActionContext& actionContext, EOrbDeactivateReason reason) override
	{
		OnDeactivateInvoked++;
		Super::OnDeactivate(executionContext, actionContext, reason);
	}

	virtual void OnSimulate(const FOrbExecutionContext& executionContext, const FOrbActionContext& actionContext) override
	{
		OnSimulateInvoked++;
		Super::OnSimulate(executionContext, actionContext);
	}

	virtual void OnEffect(const FOrbEffectContext& effectContext, const FOrbActionEffectContext& actionContext) override
	{
		OnEffectInvoked++;
		Super::OnEffect(effectContext, actionContext);
	}

	virtual bool CanForget(const FOrbObserveContext& currentContext, const FOrbActionObserveContext& actionContext, const FOrbTime& deactivationTime) override
	{
		CanForgetInvoked++;
		return Super::CanForget(currentContext, actionContext, deactivationTime);
	}

	int32 ConfigureInvoked = 0;
	int32 CanActivateInvoked= 0;
	int32 CanDeactivateInvoked= 0;
	int32 OnActivateInvoked= 0;
	int32 OnDeactivateInvoked= 0;
	int32 OnSimulateInvoked= 0;
	int32 OnEffectInvoked= 0;
	int32 CanForgetInvoked= 0;
};