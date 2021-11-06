#pragma once

#include "CoreMinimal.h"
#include "ProjectileBase.generated.h"

class UProjectileMovementComponent;

UCLASS()
class DESTRUCTIVEFORCE_API AProjectileBase : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UProjectileMovementComponent* ProjectileMovementComponent;

public:
	AProjectileBase();
};
