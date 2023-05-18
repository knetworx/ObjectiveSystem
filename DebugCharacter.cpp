// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugCharacter.h"
#include "VisualLogger/VisualLogger.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ADebugCharacter::ADebugCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADebugCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADebugCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if ENABLE_VISUAL_LOG
	UCapsuleComponent* Capsule = GetCapsuleComponent();
	if (Capsule != nullptr)
	{
		FName HeadBone = "Head";
		FVector HeadLocation = GetMesh()->GetBoneLocation(HeadBone, EBoneSpaces::WorldSpace);
		if (HeadLocation.Equals(FVector::ZeroVector))
		{
			// Approximate
			HeadLocation = GetActorLocation() + FVector::UpVector * (Capsule->GetUnscaledCapsuleHalfHeight() - 15);
		}
		UE_VLOG_CAPSULE(this, LogTemp, Verbose, GetActorLocation() - FVector::UpVector * Capsule->GetUnscaledCapsuleHalfHeight(), Capsule->GetUnscaledCapsuleHalfHeight(), Capsule->GetUnscaledCapsuleRadius(), FQuat::Identity, FColor::White, TEXT(""));
		UE_VLOG_ARROW(this, LogTemp, Verbose, HeadLocation, HeadLocation + GetActorForwardVector() * 100, FColor::Blue, TEXT(""));
		UE_VLOG_LOCATION(this, LogTemp, Verbose, GetActorLocation(), 30, FColor::Green, TEXT("Location"));
		UE_VLOG_LOCATION(this, LogTemp, Verbose, HeadLocation, 30, FColor::Red, TEXT("Character"));
	}
#endif
}

// Called to bind functionality to input
void ADebugCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

