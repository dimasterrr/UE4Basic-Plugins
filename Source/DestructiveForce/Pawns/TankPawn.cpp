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
	const auto CurrentController = Cast<ATankPlayerController>(GetController());
	if (!CurrentController) return;

	const auto CurrentLocation = GetActorLocation();
	const auto CurrentTurretRotation = WeaponSetupPoint->GetComponentRotation();
	const auto CurrentMousePosition = CurrentController->GetCurrentMousePosition();

	auto TargetTurretRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, CurrentMousePosition);
	TargetTurretRotation.Pitch = CurrentTurretRotation.Pitch;
	TargetTurretRotation.Roll = CurrentTurretRotation.Roll;

	const auto NewTurretRotation = FMath::Lerp(CurrentTurretRotation, TargetTurretRotation,
	                                           TurretRotationInterpolationSpeed);
	WeaponSetupPoint->SetWorldRotation(NewTurretRotation);
}
