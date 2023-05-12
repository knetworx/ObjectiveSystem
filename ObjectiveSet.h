// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Objective.h"
#include "ObjectiveSet.generated.h"

UENUM()
enum class ECombinerType : uint8
{
	AND,
	OR,
	SEQUENCE
};

/**
 * 
 */
UCLASS()
class FIRSTPERSONPROJECT_API AObjectiveSet : public AObjective
{
	GENERATED_BODY()
	
public:

	AObjectiveSet() { ObjectiveType = EObjectiveType::SET; }

	// Collection of objectives that will be combined for this set
	UPROPERTY(EditAnywhere)
	TArray<AObjective*> Objectives;

	// Method of combining these objectives
	UPROPERTY(EditAnywhere)
	ECombinerType CombinerType;

	UFUNCTION(BlueprintCallable)
	void UpdateProgress();

	void Activate() override;

	void Deactivate() override;
private:

	// TODO: Implement objective progression
	int CurrentObjectiveIndex = 0;

	UFUNCTION()
	void HandleObjectiveProgress();

	UFUNCTION()
	void HandleObjectiveComplete();
};
