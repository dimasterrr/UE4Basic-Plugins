#include "ProjectileBase.h"

#include "GameFramework/ProjectileMovementComponent.h"

AProjectileBase::AProjectileBase()
{
	RootComponent = Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
}
