#include "TankPlayerController.h"
#include "Kismet/KismetMathLibrary.h"

ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PerformMousePosition(DeltaSeconds);
}

void ATankPlayerController::PerformMousePosition(const float DeltaSeconds)
{
	if (!PossessedPawn) return;

	FVector MousePosition, MouseDirection;
	DeprojectMousePositionToWorld(MousePosition, MouseDirection);

	const auto PawnPosition = PossessedPawn->GetActorLocation();

	auto Direction = MousePosition - PlayerCameraManager->GetCameraLocation();
	Direction.Normalize();

	auto CurrentMousePosition = MousePosition + Direction * 1000.f;
	CurrentMousePosition.Z = PawnPosition.Z;
	
	const auto CurrentLocation = PossessedPawn->GetActorLocation();
	const auto CurrentTurretRotation = PossessedPawn->GetActorRotation(); // TODO: Rotation turret

	auto TargetTurretRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, CurrentMousePosition);
	TargetTurretRotation.Pitch = CurrentTurretRotation.Pitch;
	TargetTurretRotation.Roll = CurrentTurretRotation.Roll;

	PossessedPawn->SetTurretRotation(TargetTurretRotation);
}

void ATankPlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedPawn = Cast<ATankPawn>(InPawn);
}
