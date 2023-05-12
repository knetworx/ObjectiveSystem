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
			case ECombinerType::AND:
				TotalProgress += ProgressPerObjective * Objective->GetProgressPct();
				break;
			case ECombinerType::OR:
				if (Objective->GetProgressPct() > TotalProgress)
				{
					TotalProgress = Objective->GetProgressPct();
				}
				break;
			case ECombinerType::SEQUENCE:
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
	if (CombinerType == ECombinerType::SEQUENCE)
	{
		Objectives[CurrentObjectiveIndex]->Activate();
	}
	else
	{
		for (AObjective* Objective : Objectives)
		{
			Objective->OnProgress.AddDynamic(this, &AObjectiveSet::HandleObjectiveProgress);
			Objective->OnComplete.AddDynamic(this, &AObjectiveSet::HandleObjectiveComplete);
			Objective->Activate();
		}
	}
}

void AObjectiveSet::Deactivate()
{
	if (CombinerType == ECombinerType::SEQUENCE)
	{
		Objectives[CurrentObjectiveIndex]->Deactivate();
	}
	else
	{
		for (AObjective* Objective : Objectives)
		{
			Objective->OnProgress.RemoveDynamic(this, &AObjectiveSet::HandleObjectiveProgress);
			Objective->OnComplete.RemoveDynamic(this, &AObjectiveSet::HandleObjectiveComplete);
			Objective->Deactivate();
		}
	}
}

void AObjectiveSet::HandleObjectiveProgress()
{
	// Simply updating the progress should handle setting the percentage and triggering completion
	// for the ObjectiveSet if necessary, but keeping this separate in case I want to do more here
	UpdateProgress();
	if (CombinerType == ECombinerType::SEQUENCE)
	{
		if (CurrentObjectiveIndex < Objectives.Num() && Objectives[CurrentObjectiveIndex]->IsComplete())
		{
			Objectives[CurrentObjectiveIndex++]->Deactivate();
			Objectives[CurrentObjectiveIndex]->Activate();
		}
	}
}

void AObjectiveSet::HandleObjectiveComplete()
{
	HandleObjectiveProgress();
	if (GetProgressPct() == 1.0f && GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, TEXT("Objective set complete"));
	}
}
