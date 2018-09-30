// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManGameModeBase.h"


EGameState APacManGameModeBase::GetCurrentState() const
{
	return CurrentState;
}

void APacManGameModeBase::SetCurrentState(EGameState GameState)
{
	CurrentState = GameState;
}



