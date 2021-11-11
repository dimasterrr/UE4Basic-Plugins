#include "EnemyPawn.h"

#include "TankPawn.h"
#include "Components/ArrowComponent.h"
#include "DestructiveForce/Base/Health/HealthComponent.h"
#include "DestructiveForce/Weapons/WeaponBase.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AEnemyPawn::AEnemyPawn()
{
	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.bStartWithTickEnabled = true;
}

void AEnemyPawn::BeginPlay()
{
	Super::BeginPlay();

	if (const auto CurrentWeapon = GetActiveWeapon())
		CurrentWeapon->SetInfiniteAmmo(true);
}

void AEnemyPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (HealthComponent->IsDie()) return;

	PerformValidateTarget(DeltaTime);
	PerformRotateToTarget(DeltaTime);
}

void AEnemyPawn::PerformValidateTarget(const float DeltaTime)
{
	const auto CurrentWeapon = GetActiveWeapon();
	const auto StartPoint = CurrentWeapon->GetActorLocation();
	const auto StartPointForward = CurrentWeapon->GetActorForwardVector();
	const auto EndPoint = StartPoint + StartPointForward * 500.f;

	const auto DrawType = bDrawTargetTraceVisible ? EDrawDebugTrace::ForDuration : EDrawDebugTrace::None;

	FHitResult HitResult;
	UKismetSystemLibrary::LineTraceSingle(this, StartPoint, EndPoint, TraceChannel, false, {}, DrawType,
	                                      HitResult, true, FLinearColor::Red, FLinearColor::Green, 0.f);

	const auto CTarget = Cast<ATankPawn>(HitResult.GetActor());
	SetTarget(CTarget);
}

void AEnemyPawn::PerformRotateToTarget(const float DeltaTime) const
{
	if (FWaitingTargetHandle.IsValid()) return;

	const auto CurrentRotation = WeaponSetupPoint->GetComponentRotation();
	auto NewRotation = CurrentRotation;

	if (Target && IsTargetVisible())
	{
		auto RotationToTarget = UKismetMathLibrary::FindLookAtRotation(WeaponSetupPoint->GetComponentLocation(),
		                                                               Target->GetActorLocation());

		const auto CurrentWeaponRotation = WeaponSetupPoint->GetComponentRotation();
		RotationToTarget.Pitch = CurrentWeaponRotation.Pitch;
		RotationToTarget.Roll = CurrentWeaponRotation.Roll;

		NewRotation = RotationToTarget;
	}
	else
	{
		NewRotation.Yaw += PatrollingRotationSpeed;
	}

	WeaponSetupPoint->SetWorldRotation(NewRotation, true);
}

void AEnemyPawn::SetTarget(AActor* NewTarget)
{
	if (Target == NewTarget) return;

	Target = NewTarget;
	OnTargetIsChanged();
}

void AEnemyPawn::OnTargetIsChanged()
{
	if (Target) OnFireStart();
	else
	{
		OnFireStop();
		GetWorldTimerManager().SetTimer(FWaitingTargetHandle, this, &AEnemyPawn::OnWaitTargetPosition,
		                                WaitTimeWhenTargetLost, false);
	}
}

bool AEnemyPawn::IsTargetVisible() const
{
	return Target != nullptr;
}

void AEnemyPawn::OnWaitTargetPosition()
{
	FWaitingTargetHandle.Invalidate();
}

void AEnemyPawn::TakeDamage(const FDamageData& Data)
{
	Super::TakeDamage(Data);

	if (!Target) SetTarget(Data.Instigator);
}

void AEnemyPawn::OnDieEvent()
{
	Super::OnDieEvent();

	Target = nullptr;
	Destroy();
}
