#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DestructiveForce/Base/GameStructs.h"
#include "WeaponBase.generated.h"

class UArrowComponent;

UCLASS()
class DESTRUCTIVEFORCE_API AWeaponBase : public AActor
{
	GENERATED_BODY()

private:
	FTimerHandle DelayBetweenTimeHandle;
	FTimerHandle ReloadFireTimeHandle;
	FTimerHandle ReloadSpecialFireTimeHandle;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* SpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	float FireRate = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	float FireSpecialReloadTime = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Ammo")
	int32 MaxAmmoCount = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Ammo")
	int32 CurrentAmmoCount = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Ammo")
	bool InfiniteAmmo = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	UParticleSystem* FireEmitterTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	USoundBase* FireSoundTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	UParticleSystem* SpecialFireEmitterTemplate;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	USoundBase* SpecialFireSoundTemplate;

private:
	void OnFireReload();
	void OnSpecialFireReload();

	UFUNCTION(BlueprintPure)
	bool CanReload();

	UFUNCTION(BlueprintPure)
	bool CanFire() const;

	UFUNCTION(BlueprintPure)
	bool CanSpecialFire() const;

protected:
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION(BlueprintPure)
	bool HasAmmo() const;

	UFUNCTION(BlueprintCallable)
	virtual void OnReloadEvent();

	UFUNCTION(BlueprintCallable)
	virtual void OnFireEvent();

	UFUNCTION(BlueprintCallable)
	virtual void OnSpecialFireEvent();

public:
	AWeaponBase();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void Reload();

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void FireStart();

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void FireStop();

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void FireSpecialStart();

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void FireSpecialStop();
	
	UFUNCTION(BlueprintCallable, Category = "Fire")
	void AddAmmo(int Value);

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void SetInfiniteAmmo(const bool Value);
};
