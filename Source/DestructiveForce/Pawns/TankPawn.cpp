#include "TankPawn.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ATankPawn::ATankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = BodyMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Body Mesh"));;

	TurretMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Turret Mesh"));
	TurretMesh->SetupAttachment(BodyMesh);

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
}

void ATankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformMove(DeltaTime);
	PerformRotate(DeltaTime);
}

void ATankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &ATankPawn::OnMoveForward);
	PlayerInputComponent->BindAxis("TurnRight", this, &ATankPawn::OnTurnRight);
}

void ATankPawn::OnMoveForward(const float Value)
{
	ActiveForwardAxis = Value;
}

void ATankPawn::OnTurnRight(const float Value)
{
	ActiveRightAxis = Value;
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
