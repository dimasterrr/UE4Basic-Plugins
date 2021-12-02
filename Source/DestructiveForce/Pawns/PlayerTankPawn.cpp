﻿#include "PlayerTankPawn.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "DestructiveForce/Base/PlayerHUD.h"
#include "GameFramework/SpringArmComponent.h"
#include "DestructiveForce/Weapons/WeaponBase.h"

APlayerTankPawn::APlayerTankPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("Spring Arm"));
	SpringArm->SetupAttachment(BodyMesh);
	SpringArm->bDoCollisionTest = false;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritYaw = false;
	SpringArm->bInheritRoll = false;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);
}

void APlayerTankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformMove(DeltaTime);
	PerformRotate(DeltaTime);
}

void APlayerTankPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis("MoveForward", this, &APlayerTankPawn::OnMoveForward);
	PlayerInputComponent->BindAxis("TurnRight", this, &APlayerTankPawn::OnTurnRight);

	PlayerInputComponent->BindAction("Fire", IE_Pressed, this, &APlayerTankPawn::OnFireStart);
	PlayerInputComponent->BindAction("Fire", IE_Released, this, &APlayerTankPawn::OnFireStop);

	PlayerInputComponent->BindAction("FireSpecial", IE_Pressed, this, &APlayerTankPawn::OnFireSpecialStart);
	PlayerInputComponent->BindAction("FireSpecial", IE_Released, this, &APlayerTankPawn::OnFireSpecialStop);

	PlayerInputComponent->BindAction("Reload", IE_Pressed, this, &APlayerTankPawn::OnReload);
	PlayerInputComponent->BindAction("SwitchWeapon", IE_Pressed, this, &APlayerTankPawn::OnSwitchWeapon);
}

void APlayerTankPawn::OnMoveForward(const float Value)
{
	ActiveForwardAxis = Value;
}

void APlayerTankPawn::OnTurnRight(const float Value)
{
	ActiveRightAxis = Value;
}

void APlayerTankPawn::PerformMove(const float DeltaTime)
{
	const auto ActorForwardVector = GetActorForwardVector();

	AddMovementInput(ActorForwardVector, ActiveForwardAxis);
}

void APlayerTankPawn::PerformRotate(const float DeltaTime)
{
	CurrentRightRate = FMath::Lerp(CurrentRightRate, ActiveRightAxis, RotationInterpolationSpeed);

	const auto CurrentRotation = GetActorRotation();
	const auto RotateRate = RotationSpeed * CurrentRightRate * DeltaTime;
	const auto YawRotation = CurrentRotation.Yaw + RotateRate;
	const auto NewActorRotation = FRotator(0.f, YawRotation, 0.f);

	SetActorRotation(NewActorRotation);

	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.f, FColor::Red, FString(TEXT("RotateRate: %d"), RotateRate));
}

bool APlayerTankPawn::TakeDamage(const FDamageData& Data)
{
	if (const auto PlayerController = Cast<APlayerController>(GetController()))
	{
		PlayerController->PlayerCameraManager->StartCameraShake(DamageCameraShakeTemplate, DamageCameraShakeRate);
	}

	return Super::TakeDamage(Data);
}

void APlayerTankPawn::OnDieEvent()
{
	Super::OnDieEvent();

	FloatingPawnMovement->StopActiveMovement();

	const auto PlayerController = GetWorld()->GetFirstPlayerController();
	PlayerController->StopMovement();

	if (const auto PlayerHud = Cast<APlayerHUD>(PlayerController->GetHUD()))
	{
		const auto Widget = PlayerHud->ShowWidget(EWidgetID::GameOver, 10);

		FInputModeUIOnly Mode;
		Mode.SetWidgetToFocus(Widget->TakeWidget());
		Mode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
		PlayerController->SetInputMode(Mode);
		PlayerController->SetShowMouseCursor(true);
	}

	OnDieUi();
}

void APlayerTankPawn::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (const auto PlayerController = Cast<APlayerController>(NewController))
	{
		if (const auto Hud = Cast<APlayerHUD>(PlayerController->GetHUD()))
		{
			Hud->ShowWidget(EWidgetID::PlayerScreen, 0);
		}
	}
}
