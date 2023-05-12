// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveKill.h"

void AObjectiveKill::Activate()
{
	if (IsValid(TargetCharacter))
	{
		TargetCharacter->OnDeath.AddDynamic(this, &AObjectiveKill::HandleOnDeath);
	}
}

void AObjectiveKill::Deactivate()
{
	if (IsValid(TargetCharacter))
	{
		TargetCharacter->OnDeath.RemoveDynamic(this, &AObjectiveKill::HandleOnDeath);
	}
}

void AObjectiveKill::HandleOnDeath()
{
	Deactivate();
	DoComplete();
}
