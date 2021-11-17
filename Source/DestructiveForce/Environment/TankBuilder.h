#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "TankBuilder.generated.h"

class ATargetPoint;
class UArrowComponent;
class UBoxComponent;
class AEnemyTankPawn;

UCLASS()
class DESTRUCTIVEFORCE_API ATankBuilder : public AActor
{
	GENERATED_BODY()

private:
	FTimerHandle FSpawnTimerHandle;

protected:
	// Settings
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	float SpawnTime = 10.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	TSubclassOf<AEnemyTankPawn> DefaultSpawnActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	TArray<ATargetPoint*> PatrolPoints;

	// Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	UArrowComponent* SpawnPointComponent;

public:
	ATankBuilder();

protected:
	virtual void BeginPlay() override;

	virtual void OnSpawnActor();
};
