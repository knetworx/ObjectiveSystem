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
	}
}
