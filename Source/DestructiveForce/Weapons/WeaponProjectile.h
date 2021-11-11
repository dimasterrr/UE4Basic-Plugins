#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponProjectile.generated.h"

class AProjectileBase;

UCLASS()
class DESTRUCTIVEFORCE_API AWeaponProjectile : public AWeaponBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<AProjectileBase> DefaultProjectileClass;

private:
	UFUNCTION()
	void OnLaunchProjectile();

protected:
	virtual void OnFireEvent() override;
	virtual void OnSpecialFireEvent() override;

public:
	AWeaponProjectile();
};
