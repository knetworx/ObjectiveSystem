// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "DebugCharacter.h"
#include "EnemyCharacter.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnDeathDelegate);

UCLASS()
class FIRSTPERSONPROJECT_API AEnemyCharacter : public ADebugCharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

	UPROPERTY(BlueprintAssignable)
	FOnDeathDelegate OnDeath;

	UFUNCTION(BlueprintCallable)
	void BP_OnDeath();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
