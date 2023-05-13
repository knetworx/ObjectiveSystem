// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveActivate.h"

void AObjectiveActivate::Activate()
{
	Super::Activate();
	if (IsValid(TargetObject))
	{
		TargetObject->OnActivated.AddDynamic(this, &AObjectiveActivate::HandleOnActivated);
	}
}

void AObjectiveActivate::Deactivate()
{
	Super::Deactivate();
	if (IsValid(TargetObject))
	{
		TargetObject->OnActivated.RemoveDynamic(this, &AObjectiveActivate::HandleOnActivated);
	}
}

void AObjectiveActivate::HandleOnActivated()
{
	LogAndScreen(5, FColor::White, FString::Printf(TEXT("Object activated for '%s'"), *Name.ToString()));
	Deactivate();
	DoComplete();
}
