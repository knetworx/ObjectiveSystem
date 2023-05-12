// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActivatableActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnActivatedDelegate);

UCLASS()
class FIRSTPERSONPROJECT_API AActivatableActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActivatableActor();

	UPROPERTY(BlueprintAssignable)
	FOnActivatedDelegate OnActivated;

	UFUNCTION(BlueprintCallable)
	void BP_OnActivated();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
