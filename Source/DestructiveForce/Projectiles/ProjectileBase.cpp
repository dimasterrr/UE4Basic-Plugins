#include "ProjectileBase.h"

#include "GameFramework/ProjectileMovementComponent.h"

AProjectileBase::AProjectileBase()
{
	RootComponent = Mesh = CreateDefaultSubobject<USkeletalMeshComponent>("Mesh");
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
}
