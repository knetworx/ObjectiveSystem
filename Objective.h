// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Objective.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComplete);

UENUM()
enum class EObjectiveType : uint8
{
	OT_KILL,
	OT_LOCATION,
	OT_ACTIVATE,
	OT_SET
};

/**
 * 
 */
UCLASS()
class FIRSTPERSONPROJECT_API AObjective : public AActor
{
	GENERATED_BODY()

protected:
	AObjective() {}

	UFUNCTION(BlueprintCallable)
	void SetProgressPct(float Pct);

public:
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadOnly)
	EObjectiveType ObjectiveType;

	UPROPERTY(BlueprintAssignable)
	FOnComplete OnComplete;

	// Returns the current progress for this objective
	UFUNCTION(BlueprintGetter)
	virtual float GetProgressPct() const { return ProgressPct; }

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
