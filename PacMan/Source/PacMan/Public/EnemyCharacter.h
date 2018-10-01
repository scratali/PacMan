// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class PACMAN_API AEnemyCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	UPROPERTY(EditAnywhere, Category = Body)
	UStaticMeshComponent* EnemyBody;

	UPROPERTY(EditAnywhere, Category = Body)
	UMaterialInterface* DefaultMaterial;

	UPROPERTY(EditAnywhere, Category = Body)
	UMaterialInterface* VulnerableMaterial;


	// When player eat a super collectible, set all the enemies vulnerable for a certain period of time
	void SetVulnerable();

	// When time ends, clear it, make enemy invulnerable again and restore enemy's material and speed
	void SetInvulnerable();

	void SetMove(bool bMoveIt);
	void Kill();

	// Enemy re-arm; set invulnerable and restore its original speed
	void Rearm();

	bool bIsDead;

private:
	UFUNCTION()
		void MyOnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
			const FHitResult &SweepResult);

	bool bIsVulnerable;
	FTimerHandle TimerVulnerable;
};
