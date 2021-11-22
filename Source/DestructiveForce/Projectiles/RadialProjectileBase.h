#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.h"
#include "RadialProjectileBase.generated.h"

UCLASS()
class DESTRUCTIVEFORCE_API ARadialProjectileBase : public AProjectileBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	float ExplodeRadius = 300.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	float PushForce = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings")
	TEnumAsByte<ETraceTypeQuery> TraceChannel;
	
protected:
	virtual void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity) override;
};
