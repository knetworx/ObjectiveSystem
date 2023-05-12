// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectiveLocation.h"
#include <GameFramework/Character.h>

void AObjectiveLocation::Activate()
{
	if (IsValid(LocationTrigger))
	{
		LocationTrigger->OnActorBeginOverlap.AddDynamic(this, &AObjectiveLocation::HandleOnLocationReached);
	}
}

void AObjectiveLocation::Deactivate()
{
	if (IsValid(LocationTrigger))
	{
		LocationTrigger->OnActorBeginOverlap.RemoveDynamic(this, &AObjectiveLocation::HandleOnLocationReached);
	}
}

void AObjectiveLocation::HandleOnLocationReached(AActor* OverlappedActor, AActor* OtherActor)
{
	const ACharacter* Character = Cast<ACharacter>(OtherActor);
	if (IsValid(Character) && Character->IsPlayerControlled())
	{
		if (GEngine)
		{
			GEngine->AddOnScreenDebugMessage(-1, 5, FColor::White, TEXT("Location reached"));
		}
		Deactivate();
		DoComplete();
	}
}
