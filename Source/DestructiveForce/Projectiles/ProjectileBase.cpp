#include "ProjectileBase.h"

#include "DestructiveForce/Base/Health/Interfaces/DamageTaker.h"
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


	if (const auto DamageTaker = Cast<IDamageTaker>(ImpactResult.GetActor()))
	{
		FDamageData DamageData;
		DamageData.Damage = Damage;
		DamageData.Instigator = GetOwner();

		DamageTaker->TakeDamage(DamageData);
	}

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
