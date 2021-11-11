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

	SpawnPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow point"));
	SpawnPoint->SetupAttachment(Mesh);
}

void AWeaponBase::BeginPlay()
{
	Super::BeginPlay();
}

void AWeaponBase::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	DelayBetweenTimeHandle.Invalidate();
	ReloadFireTimeHandle.Invalidate();
	ReloadSpecialFireTimeHandle.Invalidate();

	Super::EndPlay(EndPlayReason);
}

bool AWeaponBase::HasAmmo() const
{
	return InfiniteAmmo || CurrentAmmoCount > 0;
}


void AWeaponBase::OnFireReload()
{
	GetWorldTimerManager().ClearTimer(ReloadFireTimeHandle);
}

void AWeaponBase::OnSpecialFireReload()
{
	GetWorldTimerManager().ClearTimer(ReloadSpecialFireTimeHandle);
}

void AWeaponBase::OnFireEvent()
{
}

void AWeaponBase::OnSpecialFireEvent()
{
}

void AWeaponBase::OnReloadEvent()
{
}

void AWeaponBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeaponBase::Reload()
{
	if (!CanReload()) return;

	OnReloadEvent();
}

bool AWeaponBase::CanReload()
{
	return false;
}

void AWeaponBase::FireStart()
{
	if (!CanFire()) return;

	GetWorldTimerManager().SetTimer(DelayBetweenTimeHandle, this, &AWeaponBase::OnFireEvent, FireRate, true, 0.f);
}

void AWeaponBase::FireStop()
{
	if (!GetWorldTimerManager().IsTimerActive(DelayBetweenTimeHandle)) return;
	GetWorldTimerManager().ClearTimer(DelayBetweenTimeHandle);

	if (GetWorldTimerManager().IsTimerActive(ReloadFireTimeHandle)) return;
	GetWorldTimerManager().SetTimer(ReloadFireTimeHandle, this, &AWeaponBase::OnFireReload, FireRate);
}

bool AWeaponBase::CanFire() const
{
	return !GetWorld()->GetTimerManager().IsTimerActive(ReloadFireTimeHandle)
		&& HasAmmo();
}

void AWeaponBase::FireSpecialStart()
{
	if (!CanSpecialFire()) return;

	OnSpecialFireEvent();
	GetWorld()->GetTimerManager().SetTimer(ReloadSpecialFireTimeHandle, this, &AWeaponBase::OnSpecialFireReload,
	                                       FireSpecialReloadTime);
}

void AWeaponBase::FireSpecialStop()
{
}

void AWeaponBase::AddAmmo(const int Value)
{
	CurrentAmmoCount = FMath::Clamp(CurrentAmmoCount + Value, 0, MaxAmmoCount);
}

bool AWeaponBase::CanSpecialFire() const
{
	return !GetWorld()->GetTimerManager().IsTimerActive(ReloadSpecialFireTimeHandle)
		&& HasAmmo();
}

void AWeaponBase::SetInfiniteAmmo(const bool Value)
{
	InfiniteAmmo = Value;
}
