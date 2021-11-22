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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Settings")
	float Damage = 20.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	UParticleSystem* BounceEmitterTemplate;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Settings|Effects")
	USoundBase* BounceSoundTemplate;

protected:
	UFUNCTION(BlueprintCallable)
	virtual void OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity);

	void ApplyDamage(const FHitResult& ImpactResult, bool& TargetIsDie) const;
	void ApplyScore(const FHitResult& ImpactResult) const;

public:
	AProjectileBase();

	UProjectileMovementComponent* GetProjectileMovementComponent() const;

protected:
	virtual void OnActivated() override;
	virtual void OnReleased() override;
};
