// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"

void AObjective::SetProgressPct(float Pct)
{
	Pct = FMath::Clamp(Pct, 0.0f, 1.0f);
	bool bDoBroadcastComplete = false;
	if (!FMath::IsNearlyEqual(ProgressPct, 1.0f) && FMath::IsNearlyEqual(Pct, 1.0f))
	{
		Pct = 1.0f;
		bDoBroadcastComplete = true;
	}
	ProgressPct = Pct;
	if (bDoBroadcastComplete)
	{
		// Completion callback may end up being unnecessary, maybe just always broadcast progress if it changes
		OnComplete.Broadcast();
	}
	else
	{
		OnProgress.Broadcast();
	}
	if (GEngine)
	{
		UEnum* Enum = StaticEnum<EObjectiveType>();
		FText EnumAsText = Enum->GetDisplayNameTextByIndex(int(ObjectiveType));
		GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, FString::Printf(TEXT("Setting percentage to %f for %s"), ProgressPct, *EnumAsText.ToString()));
	}
}
