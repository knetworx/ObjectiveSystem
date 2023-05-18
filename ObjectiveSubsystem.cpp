// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveSubsystem.h"

void UObjectiveSubsystem::ActivateMission(AObjectiveSet* Mission)
{
	DeactivateCurrentMission();

	ActiveMission = Mission;

	if (ActiveMission)
	{
		ActiveMission->OnComplete.AddDynamic(this, &UObjectiveSubsystem::OnMissionComplete);
		ActiveMission->Activate();
		OnMissionActivated.Broadcast(ActiveMission);
	}
}

void UObjectiveSubsystem::DeactivateCurrentMission()
{
	if (ActiveMission)
	{
		ActiveMission->OnComplete.RemoveDynamic(this, &UObjectiveSubsystem::OnMissionComplete);
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

void UObjectiveSubsystem::LogAndScreen(float Duration, const FColor& Color, const FString& FormattedMessage, bool bIsDebug)
{
	if (bIsDebug && !bIsSystemDebugging)
	{
		return;
	}
	UE_LOG(LogTemp, Error, TEXT("%s"), *FormattedMessage);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, FormattedMessage);
	}
}

void UObjectiveSubsystem::ForceReset(bool bOnlyActive /*= false*/)
{
	OnReset.Broadcast(bOnlyActive);
}

void UObjectiveSubsystem::OnMissionComplete()
{
	LogAndScreen(10, FColor::Green, FString::Printf(TEXT("MISSION COMPLETE: %s"), *ActiveMission->Name.ToString()));
	DeactivateCurrentMission();
	// On success, reset all objectives so they can be completed again in the future
	ForceReset(false);
}

void UObjectiveSubsystem::OnMissionFail()
{
	LogAndScreen(10, FColor::Red, FString::Printf(TEXT("MISSION FAILED: %s"), *ActiveMission->Name.ToString()));
	DeactivateCurrentMission();
	// On fail, only reset progress of active objectives, so the mission can be continued where it was left off
	ForceReset(true);
}
