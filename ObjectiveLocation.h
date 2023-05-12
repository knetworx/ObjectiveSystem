// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "ObjectiveLocation.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONPROJECT_API AObjectiveLocation : public AObjective
{
	GENERATED_BODY()
	
public:

	AObjectiveLocation() { ObjectiveType = EObjectiveType::LOCATION; }

	// The actor that will function as the location trigger
	UPROPERTY(EditAnywhere)
	TObjectPtr<AActor> LocationTrigger;

	void Activate() override;

	void Deactivate() override;

private:

	UFUNCTION()
	void HandleOnLocationReached(AActor* OverlappedActor, AActor* OtherActor);
};
