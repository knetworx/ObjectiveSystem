// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DebugProjectile.generated.h"

UCLASS()
class FIRSTPERSONPROJECT_API ADebugProjectile : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADebugProjectile();

	UFUNCTION(BlueprintCallable)
	void SetSourceActor(AActor* Source) { SourceActor = Source; }

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	AActor* SourceActor;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
