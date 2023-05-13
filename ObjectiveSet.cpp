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
			/*case ECombinerType::SEQUENCE:
				if (FMath::IsNearlyEqual(Objective->GetProgressPct(), 1.0f))
				{
					TotalProgress += ProgressPerObjective;
				}
				else
				{
					SetProgressPct(TotalProgress + ProgressPerObjective * Objective->GetProgressPct());
					return;
				}
				break;*/
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
		Objectives[CurrentObjectiveIndex]->OnProgress.AddDynamic(this, &AObjectiveSet::HandleObjectiveProgress);
		Objectives[CurrentObjectiveIndex]->OnComplete.AddDynamic(this, &AObjectiveSet::HandleObjectiveComplete);
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
	Super::Deactivate();
	if (CombinerType == ECombinerType::SEQUENCE)
	{
		Objectives[CurrentObjectiveIndex]->OnProgress.RemoveDynamic(this, &AObjectiveSet::HandleObjectiveProgress);
		Objectives[CurrentObjectiveIndex]->OnComplete.RemoveDynamic(this, &AObjectiveSet::HandleObjectiveComplete);
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

void AObjectiveSet::GenerateProgressReport()
{
	Super::GenerateProgressReport();
	for (AObjective* Objective : Objectives)
	{
		Objective->GenerateProgressReport();
	}
}

void AObjectiveSet::HandleObjectiveProgress()
{
	// Simply updating the progress should handle setting the percentage and triggering completion
	// for the ObjectiveSet if necessary, but keeping this separate in case I want to do more here
	UpdateProgress();
}

void AObjectiveSet::HandleObjectiveComplete()
{
	HandleObjectiveProgress();
	LogAndScreen(5, FColor::White, FString::Printf(TEXT("Objective set complete for '%s'"), *Name.ToString()));
	if (CombinerType == ECombinerType::SEQUENCE)
	{
		if (CurrentObjectiveIndex < Objectives.Num() && Objectives[CurrentObjectiveIndex]->IsComplete())
		{
			LogAndScreen(5, FColor::White, FString::Printf(TEXT("Deactivating index %d"), CurrentObjectiveIndex));
			Objectives[CurrentObjectiveIndex++]->Deactivate();
			if (CurrentObjectiveIndex < Objectives.Num())
			{
				LogAndScreen(5, FColor::White, FString::Printf(TEXT("Activating index %d"), CurrentObjectiveIndex));
				Objectives[CurrentObjectiveIndex]->Activate();
			}
		}
		else
		{
			LogAndScreen(5, FColor::White, TEXT("Not advancing objective for some reason"));
		}
	}
	if (IsComplete())
	{
		Deactivate();
		DoComplete();
	}
}
