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
	
protected:
	virtual void OnPossess(APawn* InPawn) override;

	ATargetPoint* GetNextPatrolPoint() const;

	void OnPatrolling();
	void OnPatrollingFinished();

	void OnFights();
	void OnFightsFinished();

	void OnWait();
	void OnWaitFinished();

	UFUNCTION(BlueprintCallable)
	void ApplyState();

public:
	ATankAIController();

	virtual void OnMoveCompleted(FAIRequestID RequestID, const FPathFollowingResult& Result) override;
};
