// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "EnemyCharacter.h"
#include "PacManGameModeBase.generated.h"


enum class EGameState : short
{
	EMenu,
	EPlaying,
	EPause,
	EWin,
	EGameOver
};


/**
 * 
 */
UCLASS()
class PACMAN_API APacManGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public:
	APacManGameModeBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	EGameState GetCurrentState() const;
	void SetCurrentState(EGameState GameState);
	void SetEnemyVulnerable();

	// Reset the game after Pacman is dead
	void ResetGame();

private:
	EGameState CurrentState;
	
	TArray<AEnemyCharacter*> Enemies;
	APlayerController* PlayerController;
};
