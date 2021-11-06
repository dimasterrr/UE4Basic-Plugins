#include "TankPawn.h"

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/BoxComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DestructiveForce/Controllers/TankPlayerController.h"
#include "DestructiveForce/Weapons/WeaponBase.h"

ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = BoxCollision = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collision"));

	BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));
	BodyMesh->SetupAttachment(BoxCollision);

	WeaponSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Weapon Point"));
	WeaponSetupPoint->AttachToComponent(BodyMesh, FAttachmentTransformRules::KeepRelativeTransform);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void ATankPawn::BeginPlay()
{
	Super::BeginPlay();

	SetWeapon(DefaultWeaponClass);
}

void ATankPawn::SetWeapon(const TSubclassOf<AWeaponBase> WeaponClass)
{
	if (!WeaponClass) return;
	if (EquipWeapons.Num() == MaxEquipWeapons) EquipWeapons.RemoveAt(EquipWeaponIndex);

	FActorSpawnParameters Parameters;
	Parameters.Instigator = this;
	Parameters.Owner = this;

	const auto NewWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, Parameters);
	NewWeapon->AttachToComponent(WeaponSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);

	EquipWeaponIndex = EquipWeapons.Add(NewWeapon);

	// TODO: Add switch weapon visibility
}

void ATankPawn::AddAmmoToWeapon(const TSubclassOf<AWeaponBase>& WeaponClass, const int Value)
{
	const auto FindWeapon = EquipWeapons.FindByPredicate([&WeaponClass](const AWeaponBase* Weapon)
	{
		return Weapon->GetClass() == WeaponClass;
	});
	if (!FindWeapon) return;

	(*FindWeapon)->AddAmmo(Value);
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformMove(DeltaTime);
	PerformRotate(DeltaTime);
	PerformRotateTurret(DeltaTime);
}

void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATankPawn::OnMoveForward);
	PlayerInputComponent->BindAxis("TurnRight", this, &ATankPawn::OnTurnRight);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATankPawn::OnFireStart);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &ATankPawn::OnFireStop);

	PlayerInputComponent->BindAction("FireSpecial", IE_Pressed, this, &ATankPawn::OnFireSpecialStart);
	PlayerInputComponent->BindAction("FireSpecial", IE_Released, this, &ATankPawn::OnFireSpecialStop);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &ATankPawn::OnReload);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &ATankPawn::OnSwitchWeapon);
}

void ATankPawn::OnMoveForward(const float Value)
{
	ActiveForwardAxis = Value;
}

void ATankPawn::OnTurnRight(const float Value)
{
	ActiveRightAxis = Value;
}

void ATankPawn::OnFireStart()
{
	const auto CurrentWeapon = GetActiveWeapon();

	if (!CurrentWeapon) return;
	CurrentWeapon->FireStart();
}

void ATankPawn::OnFireStop()
{
	const auto CurrentWeapon = GetActiveWeapon();

	if (!CurrentWeapon) return;
	CurrentWeapon->FireStop();
}

void ATankPawn::OnFireSpecialStart()
{
	const auto CurrentWeapon = GetActiveWeapon();

	if (!CurrentWeapon) return;
	CurrentWeapon->FireSpecialStart();
}

void ATankPawn::OnFireSpecialStop()
{
	const auto CurrentWeapon = GetActiveWeapon();

	if (!CurrentWeapon) return;
	CurrentWeapon->FireSpecialStop();
}

void ATankPawn::OnReload()
{
	const auto CurrentWeapon = GetActiveWeapon();

	if (!CurrentWeapon) return;
	CurrentWeapon->Reload();
}

void ATankPawn::OnSwitchWeapon()
{
	EquipWeaponIndex = (EquipWeaponIndex + 1) % FMath::Min(EquipWeapons.Num(), MaxEquipWeapons);
}

void ATankPawn::PerformMove(const float DeltaTime)
{
	CurrentForwardRate = FMath::Lerp(CurrentForwardRate, ActiveForwardAxis, InterpolationSpeed);

	const auto CurrentLocation = GetActorLocation();
	const auto ForwardVector = GetActorForwardVector();
	const auto MoveRate = MoveSpeed * CurrentForwardRate * ForwardVector * DeltaTime;
	const auto NewActorLocation = CurrentLocation + MoveRate;

	SetActorLocation(NewActorLocation, true);
}

void ATankPawn::PerformRotate(const float DeltaTime)
{
	CurrentRightRate = FMath::Lerp(CurrentRightRate, ActiveRightAxis, InterpolationSpeed);

	const auto CurrentRotation = GetActorRotation();
	const auto RotateRate = RotationSpeed * CurrentRightRate * DeltaTime;
	const auto YawRotation = CurrentRotation.Yaw + RotateRate;
	const auto NewActorRotation = FRotator(0.f, YawRotation, 0.f);

	SetActorRotation(NewActorRotation);
}

void ATankPawn::PerformRotateTurret(float DeltaTime) const
{
	const auto CurrentController = Cast<ATankPlayerController>(GetController());
	if (!CurrentController) return;

	const auto CurrentLocation = GetActorLocation();
	const auto CurrentTurretRotation = WeaponSetupPoint->GetComponentRotation();
	const auto CurrentMousePosition = CurrentController->GetCurrentMousePosition();

	auto TargetTurretRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, CurrentMousePosition);
	TargetTurretRotation.Pitch = CurrentTurretRotation.Pitch;
	TargetTurretRotation.Roll = CurrentTurretRotation.Roll;

	const auto NewTurretRotation = FMath::Lerp(CurrentTurretRotation, TargetTurretRotation,
	                                           TurretRotationInterpolationSpeed);
	WeaponSetupPoint->SetWorldRotation(NewTurretRotation);
}

AWeaponBase* ATankPawn::GetActiveWeapon() const
{
	if (EquipWeaponIndex == INDEX_NONE) return nullptr;
	return EquipWeapons[EquipWeaponIndex];
}
