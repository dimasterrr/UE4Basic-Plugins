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

	FVector MousePosition, MouseDirection;
	DeprojectMousePositionToWorld(MousePosition, MouseDirection);

	const auto PawnPosition = CurrentPawn->GetActorLocation();

	auto Direction = MousePosition - PlayerCameraManager->GetCameraLocation();
	Direction.Normalize();

	CurrentMousePosition = MousePosition + Direction * 1000.f;
	CurrentMousePosition.Z = PawnPosition.Z;

	DrawDebugLine(GetWorld(), PawnPosition, CurrentMousePosition, FColor::Blue, false, 0, 0, 5);
}

FVector ATankPlayerController::GetCurrentMousePosition() const
{
	return CurrentMousePosition;
}
