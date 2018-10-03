// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManHUD.h"
#include <ConstructorHelpers.h>
#include <Engine/Canvas.h>
#include "PacManGameModeBase.h"
#include <Kismet/GameplayStatics.h>
#include "PacManCharacter.h"




APacManHUD::APacManHUD()
{
	static ConstructorHelpers::FObjectFinder<UFont> HUDFontOb(TEXT("/Engine/EngineFonts/RobotoDistanceField"));

	if (HUDFontOb.Succeeded()) {
		HUDFont = HUDFontOb.Object;
	}
}

void APacManHUD::DrawHUD()
{
	Super::DrawHUD();

	FVector2D ScreenDimension = FVector2D(Canvas->SizeX, Canvas->SizeY);
	APacManGameModeBase* GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));

	switch (GameMode->GetCurrentState())
	{
		case EGameState::EMenu:
		{
			DrawText(TEXT("Welcome to Pac Man! \n\n Press N to start a new game\n Press P to pause the game"), FColor::White, 50, 50, HUDFont);
			break;
		}
		case EGameState::EPause:
		{
			DrawText(TEXT("Game paused"), FColor::White, 50, 50, HUDFont);
			break;
		}
		case EGameState::EPlaying:
		{
			// get the lives and set them
			APacManCharacter* PacMan = Cast<APacManCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
			if (PacMan)
			{
				FString LivesString = TEXT("Lives: ") + FString::FromInt(PacMan->Lives);
				DrawText(LivesString, FColor::Black, 50, 50, HUDFont);
			}
			break;
		}
		case EGameState::EGameOver:
		{
			DrawText(TEXT("GAME OVER! \n\n Press R to restart"), FColor::White, 50, 50, HUDFont);
			break;
		}
		
		case EGameState::EWin:
		{
			DrawText(TEXT("YOU WIN! \n\n R for another match ;)"), FColor::White, 50, 50, HUDFont);
			break;
		}

		default:
			break;
	}
}
