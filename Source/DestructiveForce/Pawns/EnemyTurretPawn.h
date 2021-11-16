#pragma once

#include "CoreMinimal.h"
#include "DestructiveForce/Base/PawnBase.h"
#include "EnemyTurretPawn.generated.h"

UCLASS()
class DESTRUCTIVEFORCE_API AEnemyTurretPawn : public APawnBase
{
	GENERATED_BODY()

private:
	FTimerHandle FWaitingTargetHandle;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	float RotationLagRate = .4f;
	
	UPROPERTY(EditDefaultsOnly, Category="Settings|Targetting")
	float PatrollingRotationSpeed = .4f;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Targetting")
	float WaitTimeWhenTargetLost = 4.f;
	
	UPROPERTY(EditDefaultsOnly, Category="Settings|Targetting")
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Targetting|Debug")
	bool bDrawTargetTraceVisible = false;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	AActor* Target;

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
	AEnemyTurretPawn();

	virtual void Tick(float DeltaTime) override;
	virtual bool TakeDamage(const FDamageData& Data) override;

	UFUNCTION(BlueprintCallable)
	void SetTarget(AActor* NewTarget);
};
