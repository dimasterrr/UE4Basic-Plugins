#include "WeaponBase.h"

#include "Components/ArrowComponent.h"
#include "Components/StaticMeshComponent.h"
#include "TimerManager.h"
#include "Engine/Engine.h"

AWeaponBase::AWeaponBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(RootComponent);

	ProjectileSpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow point"));
	ProjectileSpawnPoint->SetupAttachment(Mesh);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	AddAmmo(MaxAmmo);
	Reload();
}

void AWeaponBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	ReloadTimerHandle.Invalidate();
	ReloadSpecialTimerHandle.Invalidate();

	Super::EndPlay(EndPlayReason);
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::Reload()
{
	isReloading = false;
}

void AWeaponBase::ReloadSpecial()
{
	isReloading = false;
}

bool AWeaponBase::CanFire() const
{
	return !isReloading && CurrentAmmo > 0 && !IsSpecialFireInProgress();
}


bool AWeaponBase::CanSpecialFire() const
{
	return FireSpecialIterationCounts > 0;
}

bool AWeaponBase::IsSpecialFireInProgress() const
{
	return CurrentSpecialAmmo > 0;
}

int32 AWeaponBase::GetCurrentAmmo() const
{
	return CurrentAmmo;
}

void AWeaponBase::AddAmmo(const int32 NumAmmo)
{
	CurrentAmmo = FMath::Clamp(0, MaxAmmo, CurrentAmmo + NumAmmo);

	UE_LOG(LogTemp, Display, TEXT("AddAmmo(%d): CurrentAmmo=%d"), NumAmmo, CurrentAmmo);
}

void AWeaponBase::Fire()
{
	if (!CanFire()) return;

	if (Type == EWeaponFireType::Projectile) GEngine->
		AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - projectile");
	else GEngine->AddOnScreenDebugMessage(10, 1, FColor::Green, "Fire - trace");

	--CurrentAmmo;
	UE_LOG(LogTemp, Display, TEXT("Fire: CurrentAmmo=%d"), CurrentAmmo);

	isReloading = true;

	GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AWeaponBase::Reload, 1 / FireRate, false);
}

void AWeaponBase::FireSpecial()
{
	if (!CanFire() || !CanSpecialFire()) return;

	if (Type == EWeaponFireType::Projectile)
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Green, "Fire - projectile");
	else GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Green, "Fire - trace");

	--CurrentAmmo;
	UE_LOG(LogTemp, Display, TEXT("Special fire started: CurrentAmmo=%d"), CurrentAmmo);

	// Reset special ammo
	CurrentSpecialAmmo = FireSpecialIterationCounts;
	DoSpecialFireShot();
}

void AWeaponBase::DoSpecialFireShot()
{
	--CurrentSpecialAmmo;

	if (Type == EWeaponFireType::Projectile)
		GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Green, "SpecialFire - projectile");
	else GEngine->AddOnScreenDebugMessage(INDEX_NONE, 1, FColor::Green, "SpecialFire - trace");

	if (CurrentSpecialAmmo > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(ReloadSpecialTimerHandle, this, &AWeaponBase::DoSpecialFireShot,
		                                       FireSpecialRate, false);
	}
	else
	{
		UE_LOG(LogTemp, Display, TEXT("Special fire finished!"));

		ReloadSpecialTimerHandle.Invalidate();
		isReloading = true;
		GetWorld()->GetTimerManager().SetTimer(ReloadTimerHandle, this, &AWeaponBase::Reload, 1.f / FireRate, false);
	}
}
