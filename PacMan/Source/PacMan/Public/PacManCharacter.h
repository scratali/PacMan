// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PacManGameModeBase.h"
#include "PacManCharacter.generated.h"



UCLASS()
class PACMAN_API APacManCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APacManCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	void MoveXAxis(float AxisValue);
	void MoveYAxis(float AxisValue);
	void NewGame();
	void PauseGame();
	void RestartGame();
	void Kill();
	
public:
	UPROPERTY(EditAnywhere)
	uint8 Lives = 3;

	// Total collectibles in order to win
	uint8 CollectiblesToEat = 0;
	FVector StartPoint;

private:
	UFUNCTION()
	void MyOnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult &SweepResult);

	FVector CurrentVelocity;
	APacManGameModeBase* GameMode;
	bool bGamePaused = true;
	//bool bIsDead = false;
};
