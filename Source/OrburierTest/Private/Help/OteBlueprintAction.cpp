// Fill out your copyright notice in the Description page of Project Settings.


#include "OteBlueprintAction.h"

void UOteBlueprintAction::BpConfigure_Implementation()
{
	Super::Configure();
}

bool UOteBlueprintAction::BpCanActivate_Implementation(const FOrbObserveContext& activationContext, const FOrbActionObserveContext& actionContext, bool isExternal)
{
	return Super::CanActivate(activationContext, actionContext, isExternal);
}

bool UOteBlueprintAction::BpCanDeactivate_Implementation(const FOrbObserveContext& deactivationContext, const FOrbActionObserveContext& actionContext, bool isExternal)
{
	return Super::CanDeactivate(deactivationContext, actionContext, isExternal);
}

void UOteBlueprintAction::BpOnActivate_Implementation(const FOrbExecutionContext& executionContext, const FOrbActionContext& actionContext)
{
	Super::OnActivate(executionContext, actionContext);
}

void UOteBlueprintAction::BpOnDeactivate_Implementation(const FOrbExecutionContext& executionContext, const FOrbActionContext& actionContext, EOrbDeactivateReason reason)
{
	Super::OnDeactivate(executionContext, actionContext, reason);
}

void UOteBlueprintAction::BpOnSimulate_Implementation(const FOrbExecutionContext& executionContext, const FOrbActionContext& actionContext)
{
	Super::OnSimulate(executionContext, actionContext);
}

void UOteBlueprintAction::BpOnEffect_Implementation(const FOrbEffectContext& effectContext, const FOrbActionEffectContext& actionContext)
{
	Super::OnEffect(effectContext, actionContext);
}

bool UOteBlueprintAction::BpCanForget_Implementation(const FOrbObserveContext& currentContext, const FOrbActionObserveContext& actionContext, const FOrbTime& deactivationTime)
{
	return Super::CanForget(currentContext, actionContext, deactivationTime);
}
