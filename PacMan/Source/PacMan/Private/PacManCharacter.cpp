// Fill out your copyright notice in the Description page of Project Settings.

#include "PacManCharacter.h"
#include <Kismet/GameplayStatics.h>
#include <Components/CapsuleComponent.h>
#include "Collectible.h"
#include <EngineUtils.h>
#include <GameFramework/CharacterMovementComponent.h>


// Sets default values
APacManCharacter::APacManCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	GetCharacterMovement() ->bOrientRotationToMovement = true;
	//SetActorEnableCollision(true);

}

// Called when the game starts or when spawned
void APacManCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	GameMode = Cast<APacManGameModeBase>(UGameplayStatics::GetGameMode(this));
	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &APacManCharacter::MyOnCollision);

	//GameMode->SetCurrentState(EGameState::EPlaying);

	StartPoint = GetActorLocation();

	// find all the collectibles in the world
	for (TActorIterator<ACollectible> CollectibleItr(GetWorld()); CollectibleItr; ++CollectibleItr) {
		CollectiblesToEat++;
	}
}

// Called every frame
void APacManCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APacManCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveX", this, &APacManCharacter::MoveXAxis);
	PlayerInputComponent->BindAxis("MoveY", this, &APacManCharacter::MoveYAxis);
	PlayerInputComponent->BindAction("NewGame", IE_Pressed, this, &APacManCharacter::NewGame);
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APacManCharacter::PauseGame);
	PlayerInputComponent->BindAction("Restart", IE_Pressed, this, &APacManCharacter::RestartGame);
}

void APacManCharacter::MoveXAxis(float AxisValue)
{
	CurrentVelocity.X = AxisValue;
	if(!bGamePaused)
		AddMovementInput(CurrentVelocity);

}

void APacManCharacter::MoveYAxis(float AxisValue)
{
	CurrentVelocity.Y = AxisValue;
	if(!bGamePaused)
		AddMovementInput(CurrentVelocity);

}

void APacManCharacter::NewGame()
{
	if (GameMode->GetCurrentState() == EGameState::EMenu) {
		GameMode->SetCurrentState(EGameState::EPlaying);
		bGamePaused = false;
	}
}

void APacManCharacter::PauseGame()
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying) {
		GameMode->SetCurrentState(EGameState::EPause);
		bGamePaused = true;
	}
	else if (GameMode->GetCurrentState() == EGameState::EPause) {
		GameMode->SetCurrentState(EGameState::EPlaying);
		bGamePaused = false;
	}
}

void APacManCharacter::RestartGame()
{
	GetWorld()->GetFirstPlayerController()->ConsoleCommand(TEXT("RestartLevel"));
	bGamePaused = false;
}

void APacManCharacter::Kill()
{
	if (bGamePaused)
		return;

	bGamePaused = true;
	if (Lives == 0) {
		GameMode->SetCurrentState(EGameState::EGameOver);
	}
	else {
		GameMode->SetCurrentState(EGameState::EPause);
		SetActorLocation(StartPoint);
		GameMode->ResetGame();
		Lives--;
	}
}

void APacManCharacter::MyOnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult &SweepResult)
{
	if (GameMode->GetCurrentState() == EGameState::EPlaying)
	{
		if (OtherActor->IsA(ACollectible::StaticClass()))
		{
			ACollectible* CollectibleItem = Cast<ACollectible>(OtherActor);
			if (CollectibleItem && CollectibleItem->bIsSuperCollectible) {
				GameMode->SetEnemyVulnerable();
			}

			OtherActor->Destroy();

			if (--CollectiblesToEat == 0) {
				GameMode->SetCurrentState(EGameState::EWin);
				bGamePaused = true;
			}
		}
	}
}

