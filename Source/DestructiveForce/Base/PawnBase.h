#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Health/Interfaces/DamageTaker.h"
#include "Score/Interface/Scorable.h"
#include "PawnBase.generated.h"

class AWeaponBase;
class UBoxComponent;
class UArrowComponent;
class UStaticMeshComponent;
class UHealthComponent;

UCLASS()
class DESTRUCTIVEFORCE_API APawnBase : public APawn, public IDamageTaker, public IScorable
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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings|Weapon")
	TSubclassOf<AWeaponBase> DefaultWeaponClass;

	UPROPERTY(BlueprintReadOnly, Category = "Settings|Weapon")
	TArray<AWeaponBase*> EquipWeapons;

	UPROPERTY(BlueprintReadOnly, Category = "Settings|Weapon")
	int MaxEquipWeapons = 2;

	UPROPERTY(BlueprintReadOnly, Category = "Settings|Weapon")
	int EquipWeaponIndex = INDEX_NONE;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Score")
	int ScoreByDie = 20;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Effects")
	UParticleSystem* DamagedEmitterTemplate;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Effects")
	USoundBase* DamagedSoundTemplate;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Effects")
	UParticleSystem* DieEmitterTemplate;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Effects")
	USoundBase* DieDamagedSoundTemplate;

protected:
	virtual void BeginPlay() override;

public:
	APawnBase();

	virtual void Destroyed() override;

	UFUNCTION(BlueprintCallable)
	AWeaponBase* GetActiveWeapon() const;

	UFUNCTION(BlueprintCallable)
	void SetWeapon(TSubclassOf<AWeaponBase> WeaponClass);

	UFUNCTION(BlueprintCallable)
	void AddAmmoToWeapon(const TSubclassOf<AWeaponBase>& WeaponClass, int Value);

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
	bool IsDie() const;
	
	UFUNCTION(BlueprintCallable)
	virtual void OnDieEvent();

	virtual bool TakeDamage(const FDamageData& Data) override;

	virtual int GetDieScore() const override;
};
