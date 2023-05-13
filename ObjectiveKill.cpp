// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveKill.h"

void AObjectiveKill::Activate()
{
	Super::Activate();
	if (IsValid(TargetCharacter))
	{
		TargetCharacter->OnDeath.AddDynamic(this, &AObjectiveKill::HandleOnDeath);
	}
}

void AObjectiveKill::Deactivate()
{
	Super::Deactivate();
	if (IsValid(TargetCharacter))
	{
		TargetCharacter->OnDeath.RemoveDynamic(this, &AObjectiveKill::HandleOnDeath);
	}
}

void AObjectiveKill::HandleOnDeath()
{
	LogAndScreen(5, FColor::White, FString::Printf(TEXT("Enemy killed for '%s'"), *Name.ToString()));
	Deactivate();
	DoComplete();
}
