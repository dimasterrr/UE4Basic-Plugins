#include "ProjectileBase.h"

#include "DestructiveForce/Base/GlobalPlayerState.h"
#include "DestructiveForce/Base/Health/Interfaces/DamageTaker.h"
#include "DestructiveForce/Base/Score/Interface/Scorable.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMaterialLibrary.h"
#include "Kismet/KismetMathLibrary.h"

AProjectileBase::AProjectileBase()
{
	RootComponent = Mesh = CreateDefaultSubobject<UStaticMeshComponent>("Mesh");

	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	ProjectileMovementComponent->bShouldBounce = true;
	ProjectileMovementComponent->OnProjectileBounce.AddDynamic(this, &AProjectileBase::OnBounce);
}

UProjectileMovementComponent* AProjectileBase::GetProjectileMovementComponent() const
{
	return ProjectileMovementComponent;
}

void AProjectileBase::ApplyDamage(const FHitResult& ImpactResult, bool& TargetIsDie) const
{
	const auto DamageTaker = Cast<IDamageTaker>(ImpactResult.GetActor());
	if (!DamageTaker) return;

	FDamageData DamageData;
	DamageData.Damage = Damage;
	DamageData.HitPoint = FTransform(UKismetMathLibrary::MakeRotFromX(ImpactResult.Normal), ImpactResult.Location);
	DamageData.Owner = GetOwner();
	DamageData.Instigator = GetInstigator();

	TargetIsDie = DamageTaker->TakeDamage(DamageData);
}

void AProjectileBase::ApplyScore(const FHitResult& ImpactResult) const
{
	if (const auto Scorable = Cast<IScorable>(ImpactResult.GetActor()))
	{
		const auto PlayerState = GetInstigator()->GetPlayerState<AGlobalPlayerState>();
		if (PlayerState) PlayerState->AddScores(Scorable->GetDieScore());
	}
}

void AProjectileBase::OnBounce(const FHitResult& ImpactResult, const FVector& ImpactVelocity)
{
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), BounceEmitterTemplate, ImpactResult.Location);
	UGameplayStatics::SpawnSoundAtLocation(GetWorld(), BounceSoundTemplate, ImpactResult.Location);

	auto TargetIsDie = false;
	ApplyDamage(ImpactResult, TargetIsDie);
	
	if (TargetIsDie) ApplyScore(ImpactResult);

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
