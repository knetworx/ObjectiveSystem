// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Objective.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnProgress);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnComplete);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnFail);

/**
 * 
 */
UCLASS()
class FIRSTPERSONPROJECT_API AObjective : public AActor
{
	GENERATED_BODY()

protected:
	AObjective();

	UFUNCTION(BlueprintCallable)
	void SetProgressPct(float Pct);

public:

	virtual void BeginPlay() override;

	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	FName Name;

	UPROPERTY(BlueprintReadOnly)
	bool bIsActive = false;

	UPROPERTY(BlueprintAssignable)
	FOnProgress OnProgress;

	UPROPERTY(BlueprintAssignable)
	FOnComplete OnComplete;

	UPROPERTY(BlueprintAssignable)
	FOnFail OnFail;

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
	virtual void Activate();

	// Unregister for any callbacks or other cleanup necessary for this objective
	UFUNCTION(BlueprintCallable)
	virtual void Deactivate();

	// I'm not really sure what kind of failure cases we have for the existing objectives (Player/Queen dies, I guess?),
	// So I'm simply providing a blueprint callable function that will trigger it based on whatever conditions the
	// designer might want, with options to reset progress to 0 and deactivate (both optional because maybe you want to
	// start it over, but immediately run it again, or maybe you want to deactivate, but maintain progress)
	UFUNCTION(BlueprintCallable)
	virtual void BP_Fail(bool bReset, bool bDeactivate, bool bDoBroadcast);

	// Helper function to print both to the log and to the screen to see progress
	void LogAndScreen(float Duration, const FColor& Color, const FString& FormattedMessage, bool bIsDebug = false);

	virtual void GenerateProgressReport();

	virtual void Tick(float DeltaTime) override;

	virtual FVector GetLocationOfTarget() { return FVector::ZeroVector; }

private:

	UFUNCTION()
	void HandleReset(bool bOnlyActiveObjectives = false);

	float ProgressPct;
};
