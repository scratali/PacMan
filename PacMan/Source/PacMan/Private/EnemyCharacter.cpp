// Fill out your copyright notice in the Description page of Project Settings.

#include "EnemyCharacter.h"
#include <ConstructorHelpers.h>
#include <Components/CapsuleComponent.h>
#include <Components/StaticMeshComponent.h>
#include "AIEnemy.h"
#include <GameFramework/CharacterMovementComponent.h>
#include <TimerManager.h>
#include "PacManCharacter.h"
#include <Materials/MaterialInstanceDynamic.h>


// Sets default values
AEnemyCharacter::AEnemyCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	GetCapsuleComponent()->SetCapsuleRadius(40.0f);
	GetCapsuleComponent()->SetCapsuleHalfHeight(50.0f);
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;

	static ConstructorHelpers::FObjectFinder<UStaticMesh> CylinderObj(TEXT("StaticMesh'/Engine/BasicShapes/Cylinder.Cylinder'"));
	EnemyBody = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("EnemyBody"));
	EnemyBody->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	if (CylinderObj.Succeeded())
		EnemyBody->SetStaticMesh(CylinderObj.Object);

	EnemyBody->SetRelativeScale3D(FVector(0.7f, 0.7f, 1.0f));
	EnemyBody->AttachToComponent(RootComponent, FAttachmentTransformRules::KeepWorldTransform);

	static ConstructorHelpers::FObjectFinder<UMaterialInterface> VulnerableMat(TEXT("Material'/Game/Materials/M_Enemy_Vulnerable.M_Enemy_Vulnerable'"));
	if (VulnerableMat.Succeeded()) {
		VulnerableMaterial = VulnerableMat.Object;
		UE_LOG(LogTemp, Warning, TEXT("Vulnerable Material found. %s"), *VulnerableMaterial->GetName());
	}

	/*static ConstructorHelpers::FObjectFinder<UMaterialInterface> DefaultMat(TEXT("MaterialInstanceConstant'/Game/Materials/M_PacMan_Blue.M_PacMan_Blue'"));
	if (DefaultMat.Succeeded()) {
		DefaultMaterial = DefaultMat.Object;
		UE_LOG(LogTemp, Warning, TEXT("Default Material found. %s"), *DefaultMaterial->GetName());
	}*/
	if(DefaultMaterial != nullptr)
		EnemyBody->SetMaterial(0, DefaultMaterial);

	AIControllerClass = AAIEnemy::StaticClass();
}

// Called when the game starts or when spawned
void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (EnemyBody != nullptr) {
		EnemyBody->SetMaterial(0, DefaultMaterial);
	}
	else
		UE_LOG(LogTemp, Error, TEXT("EnemyBody is null"));

	//EnemyBody->SetMaterial(0, TheMaterial_Dyn);

	GetCapsuleComponent()->OnComponentBeginOverlap.AddDynamic(this, &AEnemyCharacter::MyOnCollision);
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


void AEnemyCharacter::SetVulnerable()
{
	// set/reset timer
	GetWorldTimerManager().SetTimer(TimerVulnerable, this, &AEnemyCharacter::SetInvulnerable, 15.0f, false);

	if (bIsVulnerable)	return;
	
	bIsVulnerable = true;

	EnemyBody->SetMaterial(0, VulnerableMaterial);

	// make the enemy run slower
	GetCharacterMovement()->MaxWalkSpeed = 100.0f;

	AAIEnemy* AI = Cast<AAIEnemy>(GetController());
	if (AI)
		AI->GoHome();
}

void AEnemyCharacter::SetInvulnerable()
{
	GetWorldTimerManager().ClearTimer(TimerVulnerable);
	bIsVulnerable = false;
	EnemyBody->SetMaterial(0, DefaultMaterial);
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;
	SetMove(true);
}

void AEnemyCharacter::SetMove(bool bMoveIt)
{
	// need to cast the AI class and call two public functions from	here
		// if false move to its location in order to stop movements
	//AAIEnemy* AI = Cast<AAIEnemy>(AIControllerClass);
	AAIEnemy* AI = Cast<AAIEnemy>(GetController());

	if (AI == nullptr)	return;

	if (bMoveIt)
		AI->SearchNewPoint();
	else
		AI->StopMove();
}

void AEnemyCharacter::Kill()
{
	// don't kill twice
	if (bIsDead)	return;

	// if it's not dead, kill and modify its speed. the enemy will go fast at his house in order to respawn
	bIsDead = true;
	GetCharacterMovement()->MaxWalkSpeed = 300.0f;

	AAIEnemy* AI = Cast<AAIEnemy>(GetController());
	if (AI)
		AI->GoHome();
}

void AEnemyCharacter::Rearm()
{
	bIsDead = false;
	GetCharacterMovement()->MaxWalkSpeed = 150.0f;

	if (bIsVulnerable)
		SetInvulnerable();
}

void AEnemyCharacter::MyOnCollision(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex,
	bool bFromSweep, const FHitResult &SweepResult)
{
	if (OtherActor->IsA(APacManCharacter::StaticClass()))
	{
		if (bIsVulnerable)
			Kill();
		else {
			APacManCharacter* PacMan = Cast<APacManCharacter>(OtherActor);
			if (PacMan)
				PacMan->Kill();
		}
	}
}

