// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include <Components/SphereComponent.h>
#include "Collectible.generated.h"


UCLASS()
class PACMAN_API ACollectible : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ACollectible();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


	UPROPERTY(EditDefaultsOnly, Category = Collectible)
	USphereComponent* BaseCollisionComponent;

	UPROPERTY(EditDefaultsOnly, Category = Collectible)
	UStaticMeshComponent* CollectibleMesh;

	UPROPERTY(EditAnywhere, Category = Collectible)
	bool bIsSuperCollectible;
	
};
