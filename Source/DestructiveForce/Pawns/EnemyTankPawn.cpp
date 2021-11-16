#include "EnemyTankPawn.h"
#include "DestructiveForce/Controllers/TankAIController.h"
#include "DestructiveForce/Weapons/WeaponBase.h"

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

	if (const auto CurrentWeapon = GetActiveWeapon())
		CurrentWeapon->SetInfiniteAmmo(true);
}

void AEnemyTankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AEnemyTankPawn::OnDieEvent()
{
	Super::OnDieEvent();

	Destroy();
}
