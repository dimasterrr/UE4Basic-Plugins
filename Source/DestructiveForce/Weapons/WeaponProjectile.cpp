#include "WeaponProjectile.h"

#include "Components/ArrowComponent.h"
#include "DestructiveForce/DestructiveForceGameModeBase.h"
#include "DestructiveForce/Base/ActorPool/ActorPoolComponent.h"
#include "DestructiveForce/Projectiles/ProjectileBase.h"

AWeaponProjectile::AWeaponProjectile()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AWeaponProjectile::OnFireEvent()
{
	if (!HasAmmo()) return;

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
	const auto GameMode = Cast<ADestructiveForceGameModeBase>(GetWorld()->GetAuthGameMode());
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
