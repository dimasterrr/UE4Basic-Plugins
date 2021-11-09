#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PawnBase.generated.h"

class AWeaponBase;
class UBoxComponent;
class UArrowComponent;
class UStaticMeshComponent;

UCLASS()
class DESTRUCTIVEFORCE_API APawnBase : public APawn
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* WeaponSetupPoint;

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
	
	void OnFireStart();
	void OnFireStop();

	void OnFireSpecialStart();
	void OnFireSpecialStop();

	void OnReload();
	void OnSwitchWeapon();

	AWeaponBase* GetActiveWeapon() const;

public:
	APawnBase();

	UFUNCTION(BlueprintCallable)
	void SetWeapon(TSubclassOf<AWeaponBase> WeaponClass);

	UFUNCTION(BlueprintCallable)
	void AddAmmoToWeapon(const TSubclassOf<AWeaponBase>& WeaponClass, int Value);
};
