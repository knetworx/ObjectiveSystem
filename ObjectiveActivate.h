// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "ActivatableActor.h"
#include "ObjectiveActivate.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONPROJECT_API AObjectiveActivate : public AObjective
{
	GENERATED_BODY()
	
public:

	// The object that must be activated
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<AActivatableActor> TargetObject;

	void Activate() override;
	
	void Deactivate() override;
	
	FVector GetLocationOfTarget() { return TargetObject ? TargetObject->GetActorLocation() : FVector::ZeroVector; }
	
private:

	UFUNCTION()
	void HandleOnActivated();
};
