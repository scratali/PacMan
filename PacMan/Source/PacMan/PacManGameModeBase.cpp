// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManGameModeBase.h"
#include <ConstructorHelpers.h>
#include <EngineUtils.h>


APacManGameModeBase::APacManGameModeBase()
{
	// Search our custom pacman class and set it as default pawn class
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnOb(TEXT("Blueprint'/Game/Blueprints/BP_PacManCharacter'"));
	if (PlayerPawnOb.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnOb.Class;
	}
}

void APacManGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentState(EGameState::EMenu);

	PlayerController = GetWorld()->GetFirstPlayerController();

	// Find the ghosts in the scene and add them to our array
	for (TActorIterator<AEnemyCharacter> enemyItr(GetWorld()); enemyItr; ++enemyItr)
	{
		AEnemyCharacter* enemy = Cast<AEnemyCharacter>(*enemyItr);
		if (enemy) {
			Enemies.Add(enemy);
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("Number of enemies found: %d"), Enemies.Num());

	SetCurrentState(EGameState::EPlaying);

}

EGameState APacManGameModeBase::GetCurrentState() const
{
	return CurrentState;
}

void APacManGameModeBase::SetCurrentState(EGameState GameState)
{
	CurrentState = GameState;

	for (auto EnemyIter(Enemies.CreateIterator()); EnemyIter; EnemyIter++)
	{
		switch (GameState)
		{
			case EGameState::EPlaying:
				UE_LOG(LogTemp, Warning, TEXT("GameState->Playing"));
				(*EnemyIter)->SetMove(true);
				break;
			case EGameState::EWin:
				(*EnemyIter)->Destroy();
				break;
			case EGameState::EGameOver:
				(*EnemyIter)->Destroy();
				break;
			case EGameState::EPause:
				UE_LOG(LogTemp, Warning, TEXT("GameState->Pause"));
				(*EnemyIter)->SetMove(false);
				break;
			default:
				break;
		}
	}
}

// Iterate through all enemies and make them vulnerable
void APacManGameModeBase::SetEnemyVulnerable()
{
	for (auto EnemyIter(Enemies.CreateIterator()); EnemyIter; EnemyIter++)
	{
		(*EnemyIter)->SetVulnerable();
	}
}


