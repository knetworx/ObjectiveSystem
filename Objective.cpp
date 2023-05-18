// Fill out your copyright notice in the Description page of Project Settings.


#include "Objective.h"
#include "ObjectiveSubsystem.h"
#include "VisualLogger/VisualLogger.h"

AObjective::AObjective()
{
	PrimaryActorTick.bCanEverTick = true;
}

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
	LogAndScreen(5, FColor::Blue, FString::Printf(TEXT("Setting progress for '%s' to %.2f"), *Name.ToString(), ProgressPct));
	if (bDoBroadcastComplete)
	{
		// Completion callback may end up being unnecessary, maybe just always broadcast progress if it changes
		LogAndScreen(5, FColor::Cyan, FString::Printf(TEXT("Broadcasting OnComplete for '%s'"), *Name.ToString()), true);
#if ENABLE_VISUAL_LOG
		FVector TargetLocation = GetLocationOfTarget();
		UObjectiveSubsystem* ObjSub = GetGameInstance()->GetSubsystem<UObjectiveSubsystem>();
		if (ObjSub && TargetLocation != FVector::ZeroVector)
		{
			UE_VLOG_LOCATION(ObjSub, LogTemp, Verbose, TargetLocation + FVector::UpVector * 500, 100, FColor::Green, TEXT(""));
			UE_VLOG_ARROW(ObjSub, LogTemp, Verbose, TargetLocation + FVector::UpVector * 500, TargetLocation + FVector::UpVector * 125, FColor::Green, TEXT("%s"), *Name.ToString());
		}
#endif
		OnComplete.Broadcast();
	}
	else
	{
		LogAndScreen(5, FColor::Cyan, FString::Printf(TEXT("Broadcasting OnProgress for '%s'"), *Name.ToString()), true);
		OnProgress.Broadcast();
	}
}

void AObjective::BeginPlay()
{
	Super::BeginPlay();
	UObjectiveSubsystem* ObjectiveSubsystem = GetGameInstance()->GetSubsystem<UObjectiveSubsystem>();
	if (ObjectiveSubsystem)
	{
		ObjectiveSubsystem->OnReset.AddDynamic(this, &AObjective::HandleReset);
	}
}

void AObjective::Activate()
{
	bIsActive = true;
	LogAndScreen(5, FColor::Green, FString::Printf(TEXT("Activating '%s'"), *Name.ToString()));
}

void AObjective::Deactivate()
{
	bIsActive = false;
	LogAndScreen(5, FColor::Red, FString::Printf(TEXT("Deactivating '%s'"), *Name.ToString()));
}

void AObjective::BP_Fail(bool bReset, bool bDeactivate, bool bDoBroadcast)
{
	// TODO: Maybe also add a delegate to go back to the previous step in a sequential ObjectiveSet, but
	// that would also require logic to reactivate the previous objective, bring enemies back alive, etc.
	if (bReset)
	{
		SetProgressPct(0.0f);
	}
	if (bDeactivate)
	{
		Deactivate();
	}

	// Note: In reality, you might not want to broadcast a blueprint assignable delegate from a blueprint
	// callable function (presumably one would trigger the other), but I'm not sure what failure conditions
	// would be for the example objectives given, nor what the desired outcome would be when that condition
	// occurs, so here we are pretending that blueprints would, in some way, both be the trigger of the
	// failure, and also the one that ends up handling it
	if (bDoBroadcast)
	{
		OnFail.Broadcast();
	}
}

void AObjective::LogAndScreen(float Duration, const FColor& Color, const FString& FormattedMessage, bool bIsDebug)
{
	if (bIsDebug && !UObjectiveSubsystem::bIsSystemDebugging)
	{
		return;
	}
	UE_LOG(LogTemp, Warning, TEXT("%s"), *FormattedMessage);
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, Duration, Color, FormattedMessage);
	}
}

void AObjective::GenerateProgressReport()
{
	LogAndScreen(20, FColor::Purple, FString::Printf(TEXT("%s%s: %.2f"), (bIsActive ? TEXT("+ ") : TEXT("- ")), *Name.ToString(), GetProgressPct()));
}

void AObjective::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if ENABLE_VISUAL_LOG
	FVector TargetLocation = GetLocationOfTarget();
	UObjectiveSubsystem* ObjSub = GetGameInstance()->GetSubsystem<UObjectiveSubsystem>();
	if (ObjSub && TargetLocation != FVector::ZeroVector && (bIsActive || IsComplete()))
	{
		FColor Color = IsComplete() ? FColor::Green : bIsActive ? FColor::Blue : FColor::Red;
		UE_VLOG_LOCATION(ObjSub, LogTemp, Verbose, TargetLocation + FVector::UpVector * 500, 100, Color, TEXT(""));
		UE_VLOG_ARROW(ObjSub, LogTemp, Verbose, TargetLocation + FVector::UpVector * 500, TargetLocation + FVector::UpVector * 125, Color, TEXT("%s"), *Name.ToString());
	}
#endif

}

void AObjective::HandleReset(bool bOnlyActiveObjectives /*= false*/)
{
	if (!bOnlyActiveObjectives || bIsActive)
	{
		SetProgressPct(0.0f);
	}
}
