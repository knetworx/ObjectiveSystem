// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"

void AObjective::SetProgressPct(float Pct)
{
	Pct = FMath::Clamp(Pct, 0.0f, 1.0f);
	if (!FMath::IsNearlyEqual(ProgressPct, 1.0f) && FMath::IsNearlyEqual(Pct, 1.0f))
	{
		Pct = 1.0f;
		OnComplete.Broadcast();
	}
	ProgressPct = Pct;
}
