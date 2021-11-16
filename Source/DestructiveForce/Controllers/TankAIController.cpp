#include "DestructiveForce/Controllers/TankAIController.h"
#include "DestructiveForce/Pawns/EnemyTankPawn.h"
#include "Engine/TargetPoint.h"

ATankAIController::ATankAIController()
{
}

void ATankAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (ActiveState == EEnemyState::Patrolling)
	{
		OnPatrollingFinished();
	}
}

void ATankAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	PossessedPawn = Cast<AEnemyTankPawn>(InPawn);
	ApplyState();
}

ATargetPoint* ATankAIController::GetNextPatrolPoint() const
{
	if (!PossessedPawn) return nullptr;

	const auto PatrolPoints = PossessedPawn->PatrolPoints;
	if (!PatrolPoints.Num()) return nullptr;

	return PatrolPoints[FMath::RandRange(0, PatrolPoints.Max() - 1)];
}

void ATankAIController::OnPatrolling()
{
	const auto NextPatrolPoint = GetNextPatrolPoint();
	const auto NextLocation = NextPatrolPoint->GetActorLocation();
	MoveToLocation(NextLocation, PatrolAcceptanceRadius);
}

void ATankAIController::OnPatrollingFinished()
{
	ActiveState = EEnemyState::Wait;
	ApplyState();
}

void ATankAIController::OnFights()
{
	
}

void ATankAIController::OnFightsFinished()
{
	ActiveState = EEnemyState::Wait;
	ApplyState();
}

void ATankAIController::OnWait()
{
	GetWorldTimerManager().SetTimer(FWaitTimerHandle, this, &ATankAIController::OnWaitFinished, WaitDelay);
}

void ATankAIController::OnWaitFinished()
{
	GetWorldTimerManager().ClearTimer(FWaitTimerHandle);

	ActiveState = EEnemyState::Patrolling;
	ApplyState();
}

void ATankAIController::ApplyState()
{
	switch (ActiveState)
	{
	case EEnemyState::Patrolling:
		{
			OnPatrolling();
			break;
		}

	case EEnemyState::Fights:
		{
			OnFights();
			break;
		}

	default:
	case EEnemyState::Wait:
		{
			OnWait();
			break;
		}
	}
}
