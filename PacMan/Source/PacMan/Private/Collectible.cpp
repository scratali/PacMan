// Fill out your copyright notice in the Description page of Project Settings.

#include "Collectible.h"
#include <ConstructorHelpers.h>
#include <Engine/StaticMesh.h>


// Sets default values
ACollectible::ACollectible()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	SetActorEnableCollision(true);

	BaseCollisionComponent = CreateDefaultSubobject<USphereComponent>(TEXT("BaseCollisionComponent"));
	CollectibleMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("CollectibleMesh"));
	if (CollectibleMesh != nullptr)
		CollectibleMesh->AttachToComponent(BaseCollisionComponent, FAttachmentTransformRules::KeepWorldTransform);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> Sphere(TEXT("StaticMesh'/Engine/BasicShapes/Sphere.Sphere'"));
	if (Sphere.Succeeded())
		CollectibleMesh->SetStaticMesh(Sphere.Object);

	CollectibleMesh->SetWorldScale3D(FVector(0.3f, 0.3f, 0.3f));
	BaseCollisionComponent->SetSphereRadius(16);
}

// Called when the game starts or when spawned
void ACollectible::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACollectible::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

