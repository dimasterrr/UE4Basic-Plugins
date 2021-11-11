#pragma once

#include "CoreMinimal.h"
#include "DestructiveForce/Base/PawnBase.h"
#include "EnemyPawn.generated.h"

UCLASS()
class DESTRUCTIVEFORCE_API AEnemyPawn : public APawnBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Settings|Targetting")
	float PatrollingRotationSpeed = .4f;

	// UPROPERTY(EditAnywhere, BlueprintReadWrite, ReplicatedUsing=OnRep_TargetIsChanged)
	AActor* Target;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Target")
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Target|Debug")
	bool bDrawTargetTraceVisible = false;

private:
	UFUNCTION()
	void PerformValidateTarget(const float DeltaTime);

	UFUNCTION()
	void PerformRotateToTarget(const float DeltaTime) const;

	UFUNCTION()
	virtual void OnRep_TargetIsChanged();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	bool IsTargetVisible() const;

	virtual void OnDieEvent() override;

public:
	AEnemyPawn();

	virtual void Tick(float DeltaTime) override;
};
