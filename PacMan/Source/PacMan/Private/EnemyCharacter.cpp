// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include <ConstructorHelpers.h>
#include <Components/CapsuleComponent.h>
#include <Components/StaticMeshComponent.h>


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderObj(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body"));
	if (EnemyBody != nullptr && CylinderObj.Succeeded()) {
		EnemyBody->SetStaticMesh(CylinderObj.Object);
		EnemyBody->SetRelativeScale3D(FVector(0.7f, 0.7f, 1.0f));
		EnemyBody->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);
	}

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultMat(TEXT("MaterialInstanceConstant'/Game/Materials/M_PacMan_Blue.M_PacMan_Blue'"));
	if (DefaultMat.Succeeded()) {
		DefaultMaterial = DefaultMat.Object;
		UE_LOG(LogTemp, Warning, TEXT("Default Material found. %s"), *DefaultMaterial->GetName());
	}
	EnemyBody->SetMaterial(0, DefaultMaterial);
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//EnemyBody->SetMaterial(0, DefaultMaterial);
}

// Called every frame
void AEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AEnemyCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemyCharacter::MyOnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult &SweepResult)
{

}

