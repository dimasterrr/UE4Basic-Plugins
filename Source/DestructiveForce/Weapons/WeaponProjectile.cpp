#include "WeaponProjectile.h"

#include "Components/ArrowComponent.h"
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

void AWeaponProjectile::OnLaunchProjectile() const
{
	const auto StartPoint = SpawnPoint->GetComponentLocation();
	const auto StartPointRotation = SpawnPoint->GetComponentRotation();

	FActorSpawnParameters SpawnPointParameter;
	SpawnPointParameter.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	GetWorld()->SpawnActor<AProjectileBase>(DefaultProjectileClass, StartPoint, StartPointRotation,
											SpawnPointParameter);
}
