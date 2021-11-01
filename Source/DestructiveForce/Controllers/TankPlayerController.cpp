#include "TankPlayerController.h"
#include "DrawDebugHelpers.h"

ATankPlayerController::ATankPlayerController()
{
	bShowMouseCursor = true;
}

void ATankPlayerController::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	PerformMousePosition();
}

void ATankPlayerController::PerformMousePosition()
{
	const auto CurrentPawn = GetPawn();
	if (!CurrentPawn) return;

	FVector MouseDirection;
	// Convert 2D screen cursor to 3D world position
	DeprojectMousePositionToWorld(CurrentMousePosition, MouseDirection);

	// Ignore Z position
	const auto PawnPosition = CurrentPawn->GetActorLocation();
	CurrentMousePosition.Z = PawnPosition.Z;

	// Calculate and normalize cursor direction
	auto Direction = CurrentMousePosition - PawnPosition;
	Direction.Normalize();

	CurrentMousePosition = PawnPosition + Direction * 1000;

	// Debug calculated direction
	DrawDebugLine(GetWorld(), PawnPosition, CurrentMousePosition, FColor::Blue, false, 0, 0, 5);
}

FVector ATankPlayerController::GetCurrentMousePosition() const
{
	return CurrentMousePosition;
}
