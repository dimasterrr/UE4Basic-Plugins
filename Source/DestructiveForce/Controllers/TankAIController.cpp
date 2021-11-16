#include "DestructiveForce/Controllers/TankAIController.h"
#include "DestructiveForce/Pawns/EnemyTankPawn.h"
#include "DestructiveForce/Pawns/PlayerTankPawn.h"
#include "DestructiveForce/Weapons/WeaponBase.h"
#include "Engine/TargetPoint.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

ATankAIController::ATankAIController()
{
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformTarget(DeltaTime);
	PerformTurretRotation(DeltaTime);
}

void ATankAIController::PerformTarget(float DeltaTime)
{
	if (!PossessedPawn) return;

	const auto StartPoint = PossessedPawn->GetActiveWeapon()->GetActorLocation();
	const auto StartPointForward = PossessedPawn->GetActiveWeapon()->GetActorForwardVector();
	const auto EndPoint = StartPoint + StartPointForward * 500.f;

	const auto DrawType = bDrawTargetTraceVisible ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(PossessedPawn, StartPoint, EndPoint, TraceChannel, false, {}, DrawType,
	                                      HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.f);

	const auto CTarget = Cast<APlayerTankPawn>(HitResult.GetActor());
	SetTarget(CTarget);
}

void ATankAIController::PerformTurretRotation(float DeltaTime) const
{
	if (!PossessedPawn) return;

	const auto RotationToTarget = TargetActor
		                              ? UKismetMathLibrary::FindLookAtRotation(PossessedPawn->GetActorLocation(),
		                                                                       TargetActor->GetActorLocation())
		                              : PossessedPawn->GetActorRotation();

	PossessedPawn->SetTurretRotation(RotationToTarget);
}

void ATankAIController::OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result)
{
	Super::OnMoveCompleted(RequestID, Result);

	if (ActiveState == EEnemyState::Patrolling) OnPatrollingFinished();
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
	if (!NextPatrolPoint)
	{
		OnPatrollingFinished();
		return;
	}

	const auto NextLocation = NextPatrolPoint->GetActorLocation();
	MoveToLocation(NextLocation, PatrolAcceptanceRadius, true, true, false, false);
}

void ATankAIController::OnPatrollingFinished()
{
	ActiveState = EEnemyState::Wait;
	ApplyState();
}

void ATankAIController::OnFights()
{
	PossessedPawn->OnFireStart();
	MoveToActor(TargetActor, -1, false, true, false);
}

void ATankAIController::OnFightsFinished()
{
	PossessedPawn->OnFireStop();
	StopMovement();

	ActiveState = EEnemyState::Wait;
	ApplyState();
}

void ATankAIController::OnWait()
{
	GetWorldTimerManager().SetTimer(FWaitTimerHandle, this, &ATankAIController::OnWaitFinished, WaitDelay);
}

void ATankAIController::OnWaitFinished()
{
	ActiveState = EEnemyState::Patrolling;
	ApplyState();
}

void ATankAIController::ApplyState()
{
	GetWorldTimerManager().ClearTimer(FWaitTimerHandle);

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

void ATankAIController::SetTarget(AActor* NewTarget)
{
	if (TargetActor == NewTarget) return;

	TargetActor = NewTarget;
	OnTargetIsChanged();
}

void ATankAIController::OnTargetIsChanged()
{
	if (TargetActor)
	{
		ActiveState = EEnemyState::Fights;
		ApplyState();
	}
	else
	{
		OnFightsFinished();
	}
}
