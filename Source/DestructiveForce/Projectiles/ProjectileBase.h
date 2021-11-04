#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class DESTRUCTIVEFORCE_API AProjectileBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere)
	UProjectileMovementComponent* ProjectileMovementComponent;

public:
	AProjectileBase();
};
