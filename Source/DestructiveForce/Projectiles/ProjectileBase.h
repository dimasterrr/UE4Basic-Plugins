#pragma once

#include "CoreMinimal.h"
#include "DestructiveForce/Base/ActorPool/ActorPoolable.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class DESTRUCTIVEFORCE_API AProjectileBase : public AActorPoolable
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

protected:
	UFUNCTION(BlueprintCallable)
	void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);

public:
	AProjectileBase();

protected:
	virtual void OnActivated() override;
	virtual void OnReleased() override;
};
