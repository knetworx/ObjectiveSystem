// Fill out your copyright notice in the Description page of Project Settings.


#include "ActivatableActor.h"

// Sets default values
AActivatableActor::AActivatableActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AActivatableActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AActivatableActor::BP_OnActivated()
{
	OnActivated.Broadcast();
}

