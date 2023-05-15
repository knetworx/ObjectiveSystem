// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveSet.h"

void AObjectiveSet::UpdateProgress()
{
	float ProgressPerObjective = 1.0f / Objectives.Num();
	float TotalProgress = 0.0f;
	LogAndScreen(5, FColor::White, FString::Printf(TEXT("Updating progress for '%s'"), *Name.ToString()));
	if (CombinerType == ECombinerType::SEQUENCE)
	{
		// 100% for each step completed + progress on current step
		LogAndScreen(5, FColor::White, FString::Printf(TEXT("(SEQUENCE) Current step index = %i, progress = %f"), CurrentObjectiveIndex, Objectives[CurrentObjectiveIndex]->GetProgressPct()));
		TotalProgress = ProgressPerObjective * (CurrentObjectiveIndex + Objectives[CurrentObjectiveIndex]->GetProgressPct());
	}
	else
	{
		for (AObjective* Objective : Objectives)
		{
			switch (CombinerType)
			{
			case ECombinerType::AND:
				TotalProgress += ProgressPerObjective * Objective->GetProgressPct();
				LogAndScreen(5, FColor::White, FString::Printf(TEXT("(AND) Adding progress for '%s' (%f)"), *Objective->Name.ToString(), Objective->GetProgressPct()));
				break;
			case ECombinerType::OR:
				if (Objective->GetProgressPct() > TotalProgress)
				{
					TotalProgress = Objective->GetProgressPct();
					LogAndScreen(5, FColor::White, FString::Printf(TEXT("(OR) Setting best progress from '%s' (%f)"), *Objective->Name.ToString(), Objective->GetProgressPct()));
				}
				break;
			}
		}
	}
	LogAndScreen(5, FColor::White, FString::Printf(TEXT("Total progress for '%s' (%f)"), *Name.ToString(), TotalProgress));
	SetProgressPct(TotalProgress);
}

void AObjectiveSet::Activate()
{
	Super::Activate();
	if (CombinerType == ECombinerType::SEQUENCE)
	{
		if (CurrentObjectiveIndex < Objectives.Num())
		{
			ActivateSubObjective(Objectives[CurrentObjectiveIndex]);
		}
	}
	else
	{
		for (AObjective* Objective : Objectives)
		{
			ActivateSubObjective(Objective);
		}
	}
}

void AObjectiveSet::Deactivate()
{
	Super::Deactivate();
	if (CombinerType == ECombinerType::SEQUENCE)
	{
		if (CurrentObjectiveIndex < Objectives.Num())
		{
			DeactivateSubObjective(Objectives[CurrentObjectiveIndex]);
		}
	}
	else
	{
		for (AObjective* Objective : Objectives)
		{
			DeactivateSubObjective(Objective);
		}
	}
}

void AObjectiveSet::GenerateProgressReport()
{
	Super::GenerateProgressReport();
	for (AObjective* Objective : Objectives)
	{
		Objective->GenerateProgressReport();
	}
}

void AObjectiveSet::HandleSubObjectiveProgress()
{
	// Simply updating the progress should handle setting the percentage and triggering completion
	// for the ObjectiveSet if necessary, but keeping this separate in case I want to do more here
	UpdateProgress();
}

void AObjectiveSet::HandleSubObjectiveComplete()
{
	HandleSubObjectiveProgress();
	LogAndScreen(5, FColor::White, FString::Printf(TEXT("Objective set complete for '%s'"), *Name.ToString()));
	if (CombinerType == ECombinerType::SEQUENCE)
	{
		if (CurrentObjectiveIndex < Objectives.Num() && Objectives[CurrentObjectiveIndex]->IsComplete())
		{
			LogAndScreen(5, FColor::White, FString::Printf(TEXT("Deactivating index %d"), CurrentObjectiveIndex));
			DeactivateSubObjective(Objectives[CurrentObjectiveIndex++]);
			if (CurrentObjectiveIndex < Objectives.Num())
			{
				LogAndScreen(5, FColor::White, FString::Printf(TEXT("Activating index %d"), CurrentObjectiveIndex));
				ActivateSubObjective(Objectives[CurrentObjectiveIndex]);
			}
		}
		else
		{
			LogAndScreen(5, FColor::White, TEXT("Not advancing objective for some reason"));
		}
	}
}

void AObjectiveSet::ActivateSubObjective(AObjective* SubObjective)
{
	SubObjective->OnProgress.AddDynamic(this, &AObjectiveSet::HandleSubObjectiveComplete);
	SubObjective->OnComplete.AddDynamic(this, &AObjectiveSet::HandleSubObjectiveComplete);
	SubObjective->Activate();
}

void AObjectiveSet::DeactivateSubObjective(AObjective* SubObjective)
{
	SubObjective->OnProgress.RemoveDynamic(this, &AObjectiveSet::HandleSubObjectiveComplete);
	SubObjective->OnComplete.RemoveDynamic(this, &AObjectiveSet::HandleSubObjectiveComplete);
	SubObjective->Deactivate();
}
