// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Objective.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProgress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComplete);

UENUM()
enum class EObjectiveType : uint8
{
	INVALID,
	KILL,
	LOCATION,
	ACTIVATE,
	SET
};

/**
 * 
 */
UCLASS()
class FIRSTPERSONPROJECT_API AObjective : public AActor
{
	GENERATED_BODY()

protected:
	AObjective() { ObjectiveType = EObjectiveType::INVALID; }

	UFUNCTION(BlueprintCallable)
	void SetProgressPct(float Pct);

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadOnly)
	EObjectiveType ObjectiveType;

	UPROPERTY(BlueprintAssignable)
	FOnProgress OnProgress;

	UPROPERTY(BlueprintAssignable)
	FOnComplete OnComplete;

	// Returns the current progress for this objective
	UFUNCTION(BlueprintGetter)
	float GetProgressPct() const { return ProgressPct; }

	// Returns whether our progress is 100% (accounting for potential floating point errors)
	UFUNCTION(BlueprintGetter)
	bool IsComplete() const { return FMath::IsNearlyEqual(GetProgressPct(), 1.0f); }

	// Tell the objective system that this objective is complete
	UFUNCTION(BlueprintCallable)
	virtual void DoComplete() { SetProgressPct(1.0f); }

	// Register for any callbacks or other setup necessary for processing this objective
	UFUNCTION(BlueprintCallable)
	virtual void Activate() {}

	// Unregister for any callbacks or other cleanup necessary for this objective
	UFUNCTION(BlueprintCallable)
	virtual void Deactivate() {}

private:
	float ProgressPct;
};
