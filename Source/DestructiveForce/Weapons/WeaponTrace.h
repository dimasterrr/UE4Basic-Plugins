#pragma once

#include "CoreMinimal.h"
#include "WeaponBase.h"
#include "WeaponTrace.generated.h"

UCLASS()
class DESTRUCTIVEFORCE_API AWeaponTrace : public AWeaponBase
{
	GENERATED_BODY()

private:
	FTimerHandle SpecialFireRateDelay;
	int CurrentSpecialFireCount;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Settings")
	float TraceDistance = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Special")
	int MaxSpecialFireCount = 4;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Special")
	float SpecialFireRate = 2.f;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Debug")
	TEnumAsByte<ETraceTypeQuery> TraceChannel;

	UPROPERTY(EditDefaultsOnly, Category="Settings|Debug")
	bool DrawTrace = false;

private:
	void OnLaunchTrace() const;
	void OnSpecialLaunchTrace();

protected:
	virtual void OnFireEvent() override;
	virtual void OnSpecialFireEvent() override;

public:
	AWeaponTrace();
};
