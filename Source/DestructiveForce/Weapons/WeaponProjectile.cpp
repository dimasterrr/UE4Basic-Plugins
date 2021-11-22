#include "WeaponProjectile.h"

#include "Components/ArrowComponent.h"
#include "DestructiveForce/Base/MainGameModeBase.h"
#include "DestructiveForce/Base/ActorPool/ActorPoolComponent.h"
#include "DestructiveForce/Projectiles/ProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"

AWeaponProjectile::AWeaponProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformProjectilePath(DeltaTime);
}

void AWeaponProjectile::PerformProjectilePath(float DeltaTime)
{
	if (!UsePredictsProjectilePathParams && DefaultProjectileClass != nullptr) return;

	const auto DefaultProjectile = DefaultProjectileClass.GetDefaultObject();
	const auto DefaultProjectileMovement = DefaultProjectile->GetProjectileMovementComponent();

	PredictsProjectilePathParams.StartLocation = SpawnPoint->GetComponentLocation();
	PredictsProjectilePathParams.LaunchVelocity = SpawnPoint->GetForwardVector() *
		DefaultProjectileMovement->InitialSpeed;
	PredictsProjectilePathParams.OverrideGravityZ = GetWorld()->GetWorldSettings()->GetGravityZ() *
		DefaultProjectileMovement->ProjectileGravityScale;
	PredictsProjectilePathParams.ProjectileRadius = DefaultProjectile->GetSimpleCollisionRadius();

	FPredictProjectilePathResult PredictResult;
	UGameplayStatics::PredictProjectilePath(this, PredictsProjectilePathParams, PredictResult);
}

void AWeaponProjectile::OnFireEvent()
{
	if (!HasAmmo()) return;

	Super::OnFireEvent();
	OnLaunchProjectile();
	CurrentAmmoCount--;
}

void AWeaponProjectile::OnSpecialFireEvent()
{
	if (!HasAmmo()) return;

	Super::OnSpecialFireEvent();
	CurrentAmmoCount--;
}

void AWeaponProjectile::OnLaunchProjectile()
{
	const auto GameMode = Cast<AMainGameModeBase>(GetWorld()->GetAuthGameMode());
	if (!GameMode) return;

	const auto ProjectilePool = GameMode->GetProjectilePool();
	if (!ProjectilePool) return;

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnPoint->GetComponentLocation());
	SpawnTransform.SetRotation(SpawnPoint->GetComponentRotation().Quaternion());

	FActorSpawnParameters SpawnParameters;
	SpawnParameters.Owner = this;
	SpawnParameters.Instigator = GetInstigator();
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ProjectilePool->GetOrCreate(DefaultProjectileClass, SpawnTransform, SpawnParameters);
}
