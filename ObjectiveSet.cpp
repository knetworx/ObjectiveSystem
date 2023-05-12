// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveSet.h"

void AObjectiveSet::UpdateProgress()
{
	float ProgressPerObjective = 1.0f / Objectives.Num();
	float TotalProgress = 0.0f;
	for (AObjective* Objective : Objectives)
	{
		switch (CombinerType)
		{
			case ECombinerType::CT_AND:
				TotalProgress += ProgressPerObjective * Objective->GetProgressPct();
				break;
			case ECombinerType::CT_OR:
				if (Objective->GetProgressPct() > TotalProgress)
				{
					TotalProgress = Objective->GetProgressPct();
				}
				break;
			case ECombinerType::CT_SEQUENCE:
				if (FMath::IsNearlyEqual(Objective->GetProgressPct(), 1.0f))
				{
					TotalProgress += ProgressPerObjective;
				}
				else
				{
					SetProgressPct(TotalProgress + ProgressPerObjective * Objective->GetProgressPct());
					return;
				}
				break;
		}
	}
	SetProgressPct(TotalProgress);
}

void AObjectiveSet::Activate()
{
	for (AObjective* Objective : Objectives)
	{
		Objective->OnComplete.AddDynamic(this, &AObjectiveSet::HandleObjectiveComplete);
	}
}

void AObjectiveSet::Deactivate()
{
	for (AObjective* Objective : Objectives)
	{
		Objective->OnComplete.RemoveDynamic(this, &AObjectiveSet::HandleObjectiveComplete);
	}
}

void AObjectiveSet::HandleObjectiveComplete()
{
	// Simply updating the progress should handle setting the percentage and triggering completion
	// for the ObjectiveSet if necessary, but keeping this separate in case I want to do more here
	UpdateProgress();
}
