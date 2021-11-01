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
	bool isReloading = false;

	int32 CurrentAmmo = 0;
	int32 CurrentSpecialAmmo = 0;

	FTimerHandle ReloadTimerHandle;
	FTimerHandle ReloadSpecialTimerHandle;

private:
	void Reload();
	void ReloadSpecial();

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* ProjectileSpawnPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	float FireRate = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	float FireSpecialRate = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	float FireRange = 1000;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	float FireDamage = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	int32 MaxAmmo = 10;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	int32 FireSpecialIterationCounts = 0;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	EWeaponFireType Type = EWeaponFireType::Projectile;

	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	AWeaponBase();
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintPure, Category = "Fire")
	bool CanFire() const;

	UFUNCTION(BlueprintPure, Category = "Fire")
	bool CanSpecialFire() const;
	bool IsSpecialFireInProgress() const;

	UFUNCTION(BlueprintPure, Category = "Fire")
	int32 GetCurrentAmmo() const;

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void AddAmmo(int32 NumAmmo);

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void Fire();

	UFUNCTION(BlueprintCallable, Category = "Fire")
	void FireSpecial();
	void DoSpecialFireShot();
};