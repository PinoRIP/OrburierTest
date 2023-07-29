// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Action/OrbAction.h"
#include "UObject/Object.h"
#include "OrbTypes.h"
#include "Orburier/Public/Context/OrbExecutionContext.h"
#include "Orburier/Public/Context/OrbEffectContext.h"
#include "Orburier/Public/Context/OrbActionContext.h"
#include "OteBlueprintAction.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class ORBURIERTEST_API UOteBlueprintAction : public UOrbAction
{
	GENERATED_BODY()
	
public:
	virtual EOrbInstancingPolicy GetInstancingPolicy() const override { return InstancingPolicy; };

	virtual EOrbAvailabilityPolicy GetAvailabilityPolicy() const override { return AvailabilityPolicy; }

	virtual EOrbReActivationPolicy GetReActivationPolicy() const override { return ReActivationPolicy; }

	virtual EOrbActivityPolicy GetActivityPolicy() const override { return ActivityPolicy; }

	virtual const FGameplayTagContainer* GetActionTags() const override
	{
		return &ActionTags;
	}

	virtual const FGameplayTagContainer* GetCancelActionsWithTag() const override
	{
		return &CancelActionsWithTag;
	}
	
	virtual const FGameplayTagContainer* GetBlockActionsWithTag() const override
	{
		return &BlockActionsWithTag;
	}

	virtual const FGameplayTagContainer* GetActivationOwnedTags() const override
	{
		return &ActivationOwnedTags;
	}
    	
	virtual const FGameplayTagContainer* GetActivationRequiredTags() const override
	{
		return &ActivationRequiredTags;
	}

	virtual const FGameplayTagContainer* GetActivationBlockedTags() const override
	{
		return &ActivationBlockedTags;
	}
	
	virtual void Configure() override
	{
		ConfigureInvoked++;
		BpConfigure();
	}

	virtual bool CanActivate(const FOrbObserveContext& activationContext, const FOrbActionObserveContext& actionContext, bool isExternal) override
	{
		CanActivateInvoked++;
		return BpCanActivate(activationContext, actionContext, isExternal);
	}

	virtual bool CanDeactivate(const FOrbObserveContext& deactivationContext, const FOrbActionObserveContext& actionContext, bool isExternal) override
	{
		CanDeactivateInvoked++;
		return BpCanDeactivate(deactivationContext, actionContext, isExternal);
	}
	
	virtual void OnActivate(const FOrbExecutionContext& executionContext, const FOrbActionContext& actionContext) override
	{
		OnActivateInvoked++;
		BpOnActivate(executionContext, actionContext);
	}

	virtual void OnDeactivate(const FOrbExecutionContext& executionContext, const FOrbActionContext& actionContext, EOrbDeactivateReason reason) override
	{
		OnDeactivateInvoked++;
		BpOnDeactivate(executionContext, actionContext, reason);
	}

	virtual void OnSimulate(const FOrbExecutionContext& executionContext, const FOrbActionContext& actionContext) override
	{
		OnSimulateInvoked++;
		BpOnSimulate(executionContext, actionContext);
	}

	virtual void OnEffect(const FOrbEffectContext& effectContext, const FOrbActionEffectContext& actionContext) override
	{
		OnEffectInvoked++;
		BpOnEffect(effectContext, actionContext);
	}

	virtual bool CanForget(const FOrbObserveContext& currentContext, const FOrbActionObserveContext& actionContext, const FOrbTime& deactivationTime) override
	{
		CanForgetInvoked++;
		return BpCanForget(currentContext, actionContext, deactivationTime);
	}
	
	UPROPERTY(EditDefaultsOnly)
	EOrbInstancingPolicy InstancingPolicy;

	UPROPERTY(EditDefaultsOnly)
	EOrbAvailabilityPolicy AvailabilityPolicy;

	UPROPERTY(EditDefaultsOnly)
	EOrbReActivationPolicy ReActivationPolicy;

	UPROPERTY(EditDefaultsOnly)
	EOrbActivityPolicy ActivityPolicy;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer ActionTags;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer CancelActionsWithTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer BlockActionsWithTag;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer ActivationOwnedTags;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer ActivationRequiredTags;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTagContainer ActivationBlockedTags;

	UFUNCTION(BlueprintNativeEvent)
	void BpConfigure();
	
	UFUNCTION(BlueprintNativeEvent)
	bool BpCanActivate(UPARAM(ref) const FOrbObserveContext& activationContext, UPARAM(ref) const FOrbActionObserveContext& actionContext, bool isExternal);
	
	UFUNCTION(BlueprintNativeEvent)
	bool BpCanDeactivate(UPARAM(ref) const FOrbObserveContext& deactivationContext, UPARAM(ref) const FOrbActionObserveContext& actionContext, bool isExternal);

	UFUNCTION(BlueprintNativeEvent)
	void BpOnActivate(UPARAM(ref) const FOrbExecutionContext& executionContext, UPARAM(ref) const FOrbActionContext& actionContext);

	UFUNCTION(BlueprintNativeEvent)
	void BpOnDeactivate(UPARAM(ref) const FOrbExecutionContext& executionContext, UPARAM(ref) const FOrbActionContext& actionContext, EOrbDeactivateReason reason);

	UFUNCTION(BlueprintNativeEvent)
	void BpOnSimulate(UPARAM(ref) const FOrbExecutionContext& executionContext, UPARAM(ref) const FOrbActionContext& actionContext);

	UFUNCTION(BlueprintNativeEvent)
	void BpOnEffect(UPARAM(ref) const FOrbEffectContext& effectContext, UPARAM(ref) const FOrbActionEffectContext& actionContext);

	UFUNCTION(BlueprintNativeEvent)
	bool BpCanForget(UPARAM(ref) const FOrbObserveContext& currentContext, UPARAM(ref) const FOrbActionObserveContext& actionContext, const int32& deactivationTime);

	UPROPERTY(BlueprintReadOnly)
	int32 ConfigureInvoked = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 CanActivateInvoked= 0;

	UPROPERTY(BlueprintReadOnly)
	int32 CanDeactivateInvoked= 0;

	UPROPERTY(BlueprintReadOnly)
	int32 OnActivateInvoked= 0;

	UPROPERTY(BlueprintReadOnly)
	int32 OnDeactivateInvoked= 0;

	UPROPERTY(BlueprintReadOnly)
	int32 OnSimulateInvoked= 0;

	UPROPERTY(BlueprintReadOnly)
	int32 OnEffectInvoked= 0;

	UPROPERTY(BlueprintReadOnly)
	int32 CanForgetInvoked= 0;
};
