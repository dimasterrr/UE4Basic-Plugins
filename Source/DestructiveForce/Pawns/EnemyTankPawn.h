#pragma once

#include "CoreMinimal.h"
#include "TankPawn.h"
#include "EnemyTankPawn.generated.h"

class ATargetPoint;

UCLASS()
class DESTRUCTIVEFORCE_API AEnemyTankPawn : public ATankPawn
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	TArray<ATargetPoint*> PatrolPoints;

protected:
	virtual void BeginPlay() override;

public:
	AEnemyTankPawn();

	virtual void Tick(float DeltaTime) override;

	virtual void OnDieEvent() override;
};
