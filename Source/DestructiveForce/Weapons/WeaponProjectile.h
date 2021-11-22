#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "Kismet/GameplayStaticsTypes.h"
#include "WeaponProjectile.generated.h"

class AProjectileBase;

UCLASS()
class DESTRUCTIVEFORCE_API AWeaponProjectile : public AWeaponBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	TSubclassOf<AProjectileBase> DefaultProjectileClass;

	UPROPERTY(EditDefaultsOnly, Category="Settings")
	bool UsePredictsProjectilePathParams = false;

	UPROPERTY(EditDefaultsOnly, Category="Settings", meta = (EditCondition = "UsePredictsProjectilePathParams"))
	FPredictProjectilePathParams PredictsProjectilePathParams;

private:
	UFUNCTION()
	void OnLaunchProjectile();

	void PerformProjectilePath(float DeltaTime);

protected:
	virtual void OnFireEvent() override;
	virtual void OnSpecialFireEvent() override;

public:
	AWeaponProjectile();
	
	virtual void Tick(float DeltaTime) override;
};
