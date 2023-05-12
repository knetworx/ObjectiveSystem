// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveActivate.h"

void AObjectiveActivate::Activate()
{
	TargetObject->OnActivated.AddDynamic(this, &AObjectiveActivate::HandleOnActivated);
}

void AObjectiveActivate::Deactivate()
{
	TargetObject->OnActivated.RemoveDynamic(this, &AObjectiveActivate::HandleOnActivated);
}

void AObjectiveActivate::HandleOnActivated()
{
	DoComplete();
}
