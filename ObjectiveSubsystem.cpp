// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveSubsystem.h"

void UObjectiveSubsystem::ActivateMission(AObjectiveSet* Mission)
{
	DeactivateCurrentMission();

	ActiveMission = Mission;

	if (ActiveMission)
	{
		ActiveMission->Activate();
		OnMissionActivated.Broadcast(ActiveMission);
	}
}

void UObjectiveSubsystem::DeactivateCurrentMission()
{
	if (ActiveMission)
	{
		ActiveMission->Deactivate();
		OnMissionDeactivated.Broadcast(ActiveMission);
		ActiveMission = nullptr;
	}
}

void UObjectiveSubsystem::GenerateProgressReport()
{
	LogAndScreen(20, FColor::Purple, TEXT("--------------- PROGRESS REPORT ---------------"));
	if (ActiveMission)
	{
		ActiveMission->GenerateProgressReport();
	}
	else
	{
		LogAndScreen(20, FColor::Purple, TEXT("No active mission"));
	}
	LogAndScreen(20, FColor::Purple, TEXT("-----------------------------------------------"));
}

void UObjectiveSubsystem::LogAndScreen(float Duration, const FColor& Color, const FString& FormattedMessage)
{
	UE_LOG(LogTemp, Error, TEXT("%s"), *FormattedMessage);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, FormattedMessage);
	}
}
