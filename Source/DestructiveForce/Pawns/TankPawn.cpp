#include "TankPawn.h"

#include "CoreMinimal.h"
#include "Camera/CameraComponent.h"
#include "Components/ArrowComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "DestructiveForce/Controllers/TankPlayerController.h"
#include "DestructiveForce/Weapons/WeaponBase.h"

ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BodyMesh);

	WeaponSetupPoint = CreateDefaultSubobject<UArrowComponent>(TEXT("Weapon Point"));
	WeaponSetupPoint->AttachToComponent(TurretMesh, FAttachmentTransformRules::KeepRelativeTransform);

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
	SetupCannon();
}

void ATankPawn::SetupCannon()
{
	if (CurrentWeapon) CurrentWeapon->Destroy();

	FActorSpawnParameters Parameters;
	Parameters.Instigator = this;
	Parameters.Owner = this;

	CurrentWeapon = GetWorld()->SpawnActor<AWeaponBase>(WeaponClass, Parameters);
	CurrentWeapon->AttachToComponent(WeaponSetupPoint, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
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

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &ATankPawn::OnFire);
	PlayerInputComponent->BindAction("FireSpecial", IE_Pressed, this, &ATankPawn::OnFireSpecial);
}

void ATankPawn::OnMoveForward(const float Value)
{
	ActiveForwardAxis = Value;
}

void ATankPawn::OnTurnRight(const float Value)
{
	ActiveRightAxis = Value;
}

void ATankPawn::OnFire()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->Fire();
}

void ATankPawn::OnFireSpecial()
{
	if (!CurrentWeapon) return;
	CurrentWeapon->FireSpecial();
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
	const auto CurrentTurretRotation = TurretMesh->GetComponentRotation();
	const auto CurrentMousePosition = CurrentController->GetCurrentMousePosition();

	auto TargetTurretRotation = UKismetMathLibrary::FindLookAtRotation(CurrentLocation, CurrentMousePosition);
	TargetTurretRotation.Pitch = CurrentTurretRotation.Pitch;
	TargetTurretRotation.Roll = CurrentTurretRotation.Roll;

	const auto NewTurretRotation = FMath::Lerp(CurrentTurretRotation, TargetTurretRotation,
	                                           TurretRotationInterpolationSpeed);
	TurretMesh->SetWorldRotation(NewTurretRotation);
}
