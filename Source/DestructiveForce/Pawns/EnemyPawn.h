#pragma once

#include "CoreMinimal.h"
#include "DestructiveForce/Base/PawnBase.h"
#include "EnemyPawn.generated.h"

UCLASS()
class DESTRUCTIVEFORCE_API AEnemyPawn : public APawnBase
{
	GENERATED_BODY()

private:
	FTimerHandle FWaitingTargetHandle;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Settings|Targetting")
	float PatrollingRotationSpeed = .4f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Target;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Targettting")
	float WaitTimeWhenTargetLost = 4.f;

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
	void OnTargetIsChanged();

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	bool IsTargetVisible() const;
	
	UFUNCTION()
	void OnWaitTargetPosition();

	virtual void OnDieEvent() override;
public:
	AEnemyPawn();

	virtual void Tick(float DeltaTime) override;
	virtual void TakeDamage(const FDamageData& Data) override;

	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* NewTarget);
};
