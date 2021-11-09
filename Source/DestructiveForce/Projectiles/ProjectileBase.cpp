#include "ProjectileBase.h"

#include "GameFramework/ProjectileMovementComponent.h"

AProjectileBase::AProjectileBase()
{
	RootComponent = Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->OnProjectileBounce.AddDynamic(this, &AProjectileBase::OnBounce);
}

void AProjectileBase::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	// TODO: Add super effects

	Release();
}

void AProjectileBase::OnActivated()
{
	ProjectileMovementComponent->SetUpdatedComponent(RootComponent);

	const auto DefaultMovement = GetClass()->GetDefaultObject<AProjectileBase>()->ProjectileMovementComponent;
	const auto NewVelocity = DefaultMovement->InitialSpeed > 0.f
		                         ? DefaultMovement->Velocity.GetSafeNormal() * DefaultMovement->InitialSpeed
		                         : DefaultMovement->Velocity;
	ProjectileMovementComponent->SetVelocityInLocalSpace(NewVelocity);
}

void AProjectileBase::OnReleased()
{
}
