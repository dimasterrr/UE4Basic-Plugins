#include "PawnBase.h"

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DestructiveForce/Weapons/WeaponBase.h"
#include "Health/HealthComponent.h"

APawnBase::APawnBase()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	BodyMesh->SetupAttachment(BoxCollision);

	WeaponSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Weapon Point"));
	WeaponSetupPoint->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);

	HealthComponent = CreateDefaultSubobject<UHealthComponent>("HealthComponent");
	HealthComponent->OnDieDelegate.AddUObject(this, &APawnBase::OnDieEvent);
}

void APawnBase::Destroyed()
{
	Super::Destroyed();

	for (const auto& Weapon : EquipWeapons) Weapon->Destroy();
}

void APawnBase::BeginPlay()
{
	Super::BeginPlay();

	SetWeapon(DefaultWeaponClass);
}

void APawnBase::SetWeapon(const TSubclassOf<AWeaponBase> WeaponClass)
{
	if (!WeaponClass) return;
	if (EquipWeapons.Num() == MaxEquipWeapons) EquipWeapons.RemoveAt(EquipWeaponIndex);

	FActorSpawnParameters Parameters;
	Parameters.Instigator = this;
	Parameters.Owner = this;

	const auto NewWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, Parameters);
	NewWeapon->AttachToComponent(WeaponSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	EquipWeaponIndex = EquipWeapons.Add(NewWeapon);
}

void APawnBase::OnFireStart()
{
	const auto CurrentWeapon = GetActiveWeapon();

	if (!CurrentWeapon) return;
	CurrentWeapon->FireStart();
}

void APawnBase::OnFireStop()
{
	const auto CurrentWeapon = GetActiveWeapon();

	if (!CurrentWeapon) return;
	CurrentWeapon->FireStop();
}

void APawnBase::OnFireSpecialStart()
{
	const auto CurrentWeapon = GetActiveWeapon();

	if (!CurrentWeapon) return;
	CurrentWeapon->FireSpecialStart();
}

void APawnBase::OnFireSpecialStop()
{
	const auto CurrentWeapon = GetActiveWeapon();

	if (!CurrentWeapon) return;
	CurrentWeapon->FireSpecialStop();
}

void APawnBase::OnReload()
{
	const auto CurrentWeapon = GetActiveWeapon();

	if (!CurrentWeapon) return;
	CurrentWeapon->Reload();
}

void APawnBase::OnSwitchWeapon()
{
	OnFireStop();

	EquipWeaponIndex = (EquipWeaponIndex + 1) % FMath::Min(EquipWeapons.Num(), MaxEquipWeapons);
}

void APawnBase::OnDieEvent()
{
	OnFireStop();
}

AWeaponBase* APawnBase::GetActiveWeapon() const
{
	if (EquipWeaponIndex == INDEX_NONE) return nullptr;
	return EquipWeapons[EquipWeaponIndex];
}

void APawnBase::AddAmmoToWeapon(const TSubclassOf<AWeaponBase>& WeaponClass, const int Value)
{
	const auto FindWeapon = EquipWeapons.FindByPredicate([&WeaponClass](const AWeaponBase* Weapon)
	{
		return Weapon->GetClass() == WeaponClass;
	});
	if (!FindWeapon) return;

	(*FindWeapon)->AddAmmo(Value);
}

bool APawnBase::TakeDamage(const FDamageData& Data)
{
	const auto CurrentHealth = HealthComponent->GetHealth();
	HealthComponent->SetHealth(CurrentHealth - Data.Damage);

	return HealthComponent->IsDie();
}

int APawnBase::GetDieScore() const
{
	return ScoreByDie;
}
