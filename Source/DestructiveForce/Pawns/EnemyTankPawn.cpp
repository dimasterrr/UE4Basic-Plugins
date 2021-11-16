#include "EnemyTankPawn.h"
#include "DestructiveForce/Controllers/TankAIController.h"

AEnemyTankPawn::AEnemyTankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	bUseControllerRotationYaw = true;
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
	AIControllerClass = ATankAIController::StaticClass();
}

void AEnemyTankPawn::BeginPlay()
{
	Super::BeginPlay();
}

void AEnemyTankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}