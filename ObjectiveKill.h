// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Objective.h"
#include "EnemyCharacter.h"
#include "ObjectiveKill.generated.h"

/**
 * 
 */
UCLASS()
class FIRSTPERSONPROJECT_API AObjectiveKill : public AObjective
{
	GENERATED_BODY()
	
public:
	AObjectiveKill() { ObjectiveType = EObjectiveType::KILL; }

	// The enemy we want to kill
	UPROPERTY(BlueprintReadOnly, EditAnywhere)
	TObjectPtr<AEnemyCharacter> TargetCharacter;

	void Activate() override;

	void Deactivate() override;

private:

	UFUNCTION()
	void HandleOnDeath();
};
