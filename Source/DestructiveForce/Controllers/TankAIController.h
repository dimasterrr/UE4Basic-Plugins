#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "DestructiveForce/Pawns/EnemyTankPawn.h"
#include "TankAIController.generated.h"

UENUM()
enum EEnemyState
{
	Wait,
	Patrolling,
	Fights
};

UCLASS()
class DESTRUCTIVEFORCE_API ATankAIController : public AAIController
{
	GENERATED_BODY()

private:
	FTimerHandle FWaitTimerHandle;

protected:
	UPROPERTY(BlueprintReadOnly, Category="Settings")
	AEnemyTankPawn* PossessedPawn;

	UPROPERTY(BlueprintReadWrite, Category="Settings")
	TEnumAsByte<EEnemyState> ActiveState = EEnemyState::Wait;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings|Patrol")
	float WaitDelay = 6.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings|Patrol")
	float PatrolAcceptanceRadius = 10.f;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Targetting")
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Targetting|Debug")
	bool bDrawTargetTraceVisible = false;

	UPROPERTY(BlueprintReadOnly)
	AActor* TargetActor = nullptr;

private:
	void OnWait();
	void OnPatrolling();
	void OnFights();
	void OnWaitFinished();
	void OnPatrollingFinished();
	void OnFightsFinished();
	void OnTargetIsChanged();
	
	void PerformTarget(float DeltaTime);
	void PerformTurretRotation(float DeltaTime) const;

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UFUNCTION(BlueprintCallable)
	ATargetPoint* GetNextPatrolPoint() const;

	UFUNCTION(BlueprintCallable)
	void ApplyState();

	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* NewTarget);

public:
	ATankAIController();

	virtual void Tick(float DeltaTime) override;
	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
