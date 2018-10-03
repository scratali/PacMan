// Fill out your copyright notice in the Description page of Project Settings.

#include "AIEnemy.h"
#include <TimerManager.h>
#include <NavigationSystem.h>
#include <DrawDebugHelpers.h>



AAIEnemy::AAIEnemy()
{
}

// When possessed, store its location and start to move around
void AAIEnemy::Possess(APawn* InPawn)
{
	Super::Possess(InPawn);

	Bot = Cast<AEnemyCharacter>(InPawn);
	SearchNewPoint();
}


void AAIEnemy::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	if (!Bot->bIsDead && Result.IsSuccess())
		SearchNewPoint();
}

// In order to find a new point we search if there is a navigation mesh active and
//     when found, we simply call the GetRandomPointInRadius function from the NavMesh
void AAIEnemy::SearchNewPoint()
{
	UNavigationSystemV1* NavMesh = UNavigationSystemV1::GetCurrent(this);
	//UNavigationSystemV1* NavMesh = FNavigationSystem::GetCurrent<UNavigationSystemV1>(GetWorld());
	//UNavigationSystemV1* NavMesh = UNavigationSystemV1::GetCurrent(GetWorld());
	if (NavMesh) {
		const float fSearchRadius = 10000.0f;
		FNavLocation RandomPt;
		bool bFound = NavMesh->GetRandomReachablePointInRadius(Bot->GetActorLocation(), fSearchRadius, RandomPt);
		if (bFound) {
			DrawDebugPoint(GetWorld(), RandomPt.Location, 10, FColor(255, 0, 0), true, 10);
			MoveToLocation(RandomPt.Location);
		}
	}
}

// Simply return to home location and start a timer for death
void AAIEnemy::GoHome()
{
	MoveToLocation(Bot->GetHomeLocation());
	GetWorldTimerManager().SetTimer(TimerDead, this, &AAIEnemy::Rearm, 5.0f, false);
}

// Clear the timer and return to walk
void AAIEnemy::Rearm()
{
	GetWorldTimerManager().ClearTimer(TimerDead);
	Bot->Rearm();
}

void AAIEnemy::StopMove()
{
	StopMovement();
}

