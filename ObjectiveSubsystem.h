// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ObjectiveSet.h"
#include "ObjectiveSubsystem.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissionActivated, AObjectiveSet*, Mission);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMissionDeactivated, AObjectiveSet*, Mission);

/**
 * 
 */
UCLASS()
class FIRSTPERSONPROJECT_API UObjectiveSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:

	UPROPERTY(BlueprintAssignable)
	FOnMissionActivated OnMissionActivated;

	UPROPERTY(BlueprintAssignable)
	FOnMissionDeactivated OnMissionDeactivated;

	// Add a mission (can be a single Objective or an ObjectiveSet for missions containing multiple objectives)
	UFUNCTION(BlueprintCallable)
	void ActivateMission(AObjectiveSet* Mission);
	
	UFUNCTION(BlueprintCallable)
	void DeactivateCurrentMission();

private:
	TObjectPtr<AObjectiveSet> ActiveMission;
};
