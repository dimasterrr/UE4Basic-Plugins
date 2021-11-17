#pragma once

#include "CoreMinimal.h"
#include "DestructiveForce/Base/Health/Interfaces/DamageTaker.h"
#include "GameFramework/Actor.h"
#include "TankBuilder.generated.h"

class UHealthComponent;
class ATargetPoint;
class UArrowComponent;
class UBoxComponent;
class AEnemyTankPawn;

UCLASS()
class DESTRUCTIVEFORCE_API ATankBuilder : public AActor, public IDamageTaker
{
	GENERATED_BODY()

private:
	FTimerHandle FSpawnTimerHandle;

protected:
	// Settings
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	float SpawnMax = 4;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	float SpawnTime = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	TSubclassOf<AEnemyTankPawn> DefaultSpawnActor;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	TArray<ATargetPoint*> PatrolPoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	UParticleSystem* SpawnEmitterTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	USoundBase* SpawnSoundTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	UParticleSystem* DamagedEmitterTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	USoundBase* DamagedSoundTemplate;

	// Components
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	UArrowComponent* SpawnEffectsComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	UArrowComponent* SpawnPointComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Components")
	UHealthComponent* HealthComponent;

protected:
	virtual void BeginPlay() override;

	virtual void OnSpawnActor();

public:
	ATankBuilder();

	UFUNCTION()
	virtual bool TakeDamage(const FDamageData& Data) override;

	UFUNCTION(BlueprintNativeEvent)
	void OnDie();

	UFUNCTION()
	UHealthComponent* GetHealthComponent() const;
};
