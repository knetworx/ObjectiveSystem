// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveActivate.h"

void AObjectiveActivate::Activate()
{
	if (IsValid(TargetObject))
	{
		TargetObject->OnActivated.AddDynamic(this, &AObjectiveActivate::HandleOnActivated);
	}
}

void AObjectiveActivate::Deactivate()
{
	if (IsValid(TargetObject))
	{
		TargetObject->OnActivated.RemoveDynamic(this, &AObjectiveActivate::HandleOnActivated);
	}
}

void AObjectiveActivate::HandleOnActivated()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, TEXT("Object activated"));
	}
	Deactivate();
	DoComplete();
}
