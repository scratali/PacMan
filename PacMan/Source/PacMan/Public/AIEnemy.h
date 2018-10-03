// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "EnemyCharacter.h"
#include "AIEnemy.generated.h"

/**
 * 
 */
UCLASS()
class PACMAN_API AAIEnemy : public AAIController
{
	GENERATED_BODY()
	
public:

	AAIEnemy();

	void Possess(APawn* InPawn) override;
	
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;

	void SearchNewPoint();
	void GoHome();
	void Rearm();
	void StopMove();

private:
	AEnemyCharacter* Bot;
	FTimerHandle TimerDead;
};
