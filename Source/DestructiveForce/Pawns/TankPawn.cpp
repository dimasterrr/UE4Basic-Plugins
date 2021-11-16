#include "TankPawn.h"

#include "CoreMinimal.h"
#include "Components/ArrowComponent.h"
#include "DestructiveForce/Weapons/WeaponBase.h"
#include "DestructiveForce/Controllers/TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	FloatingPawnMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Floating Pawn Movement"));
	FloatingPawnMovement->MaxSpeed = 100.f;
	FloatingPawnMovement->SetPlaneConstraintEnabled(true);
	FloatingPawnMovement->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Z);
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformRotateTurret(DeltaTime);
}

void ATankPawn::PerformRotateTurret(float DeltaTime) const
{
	const auto CurrentRotation = WeaponSetupPoint->GetComponentRotation();
	const auto NewRotation = FMath::Lerp(CurrentRotation, CurrentTurretRotation, TurretRotationInterpolationSpeed);

	WeaponSetupPoint->SetWorldRotation(NewRotation);
}

void ATankPawn::SetTurretRotation(const FRotator Value)
{
	CurrentTurretRotation = Value;
}
