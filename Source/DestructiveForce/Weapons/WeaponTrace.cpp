#include "WeaponTrace.h"

#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"

AWeaponTrace::AWeaponTrace()
{
	PrimaryActorTick.bCanEverTick = true;
}

AWeaponTrace::~AWeaponTrace()
{
	SpecialFireRateDelay.Invalidate();
}

void AWeaponTrace::OnFireEvent()
{
	if (!HasAmmo()) return;

	OnLaunchTrace();
	--CurrentAmmoCount;
}

void AWeaponTrace::OnSpecialFireEvent()
{
	if (!HasAmmo()) return;

	CurrentSpecialFireCount = MaxSpecialFireCount;
	GetWorldTimerManager().SetTimer(SpecialFireRateDelay, this, &AWeaponTrace::OnSpecialLaunchTrace, SpecialFireRate,
									true, 0.f);
	--CurrentAmmoCount;
}

void AWeaponTrace::OnLaunchTrace() const
{
	const auto StartPoint = SpawnPoint->GetComponentLocation();
	const auto StartPointForward = SpawnPoint->GetForwardVector();
	const auto EndPoint = StartPoint + StartPointForward * TraceDistance;
	const auto DrawType = DrawTrace ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(this, StartPoint, EndPoint, TraceChannel, false, {}, DrawType,
										  HitResult, true);
}

void AWeaponTrace::OnSpecialLaunchTrace()
{
	OnLaunchTrace();
	--CurrentSpecialFireCount;

	if (CurrentSpecialFireCount == 0)
		GetWorldTimerManager().ClearTimer(SpecialFireRateDelay);
}
