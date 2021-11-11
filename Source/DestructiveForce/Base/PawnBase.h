#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Health/Interfaces/DamageTaker.h"
#include "PawnBase.generated.h"

class AWeaponBase;
class UBoxComponent;
class UArrowComponent;
class UStaticMeshComponent;
class UHealthComponent;

UCLASS()
class DESTRUCTIVEFORCE_API APawnBase : public APawn, public IDamageTaker
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* WeaponSetupPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UHealthComponent* HealthComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Weapon")
	TSubclassOf<AWeaponBase> DefaultWeaponClass;

	UPROPERTY(BlueprintReadOnly, Category = "Turret|Weapon")
	TArray<AWeaponBase*> EquipWeapons;

	UPROPERTY(BlueprintReadOnly, Category = "Turret|Weapon")
	int MaxEquipWeapons = 2;

	UPROPERTY(BlueprintReadOnly, Category = "Turret|Weapon")
	int EquipWeaponIndex = INDEX_NONE;

protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	void OnFireStart();

	UFUNCTION(BlueprintCallable)
	void OnFireStop();

	UFUNCTION(BlueprintCallable)
	void OnFireSpecialStart();

	UFUNCTION(BlueprintCallable)
	void OnFireSpecialStop();

	UFUNCTION(BlueprintCallable)
	void OnReload();

	UFUNCTION(BlueprintCallable)
	void OnSwitchWeapon();

	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetActiveWeapon() const;

	UFUNCTION(BlueprintCallable)
	virtual void OnDieEvent();

public:
	APawnBase();

	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable)
	void SetWeapon(TSubclassOf<AWeaponBase> WeaponClass);

	UFUNCTION(BlueprintCallable)
	void AddAmmoToWeapon(const TSubclassOf<AWeaponBase>& WeaponClass, int Value);

	virtual void TakeDamage(const FDamageData& Data) override;
};
