// Fill out your copyright notice in the Description page of Project Settings.


#include "DebugProjectile.h"
#include "VisualLogger/VisualLogger.h"

// Sets default values
ADebugProjectile::ADebugProjectile()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADebugProjectile::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADebugProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

#if ENABLE_VISUAL_LOG
	UE_VLOG_LOCATION(SourceActor, LogTemp, Verbose, GetActorLocation(), 30, FColor::Yellow, TEXT("Projectile"));
#endif
}

