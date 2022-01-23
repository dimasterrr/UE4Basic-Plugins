#include "PlayerTankPawn.h"

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "DestructiveForce/Base/PlayerHUD.h"
#include "GameFramework/SpringArmComponent.h"
#include "DestructiveForce/Weapons/WeaponBase.h"
#include "Modules/Inventory/Components/InventoryComponent.h"
#include "Modules/Inventory/Components/InventoryEquipComponent.h"
#include "Modules/Inventory/Components/InventoryManagerComponent.h"

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

	InventoryComponent = CreateDefaultSubobject<UInventoryComponent>(TEXT("Inventory Component"));
	InventoryEquipComponent = CreateDefaultSubobject<UInventoryEquipComponent>(TEXT("Inventory Equip Component"));
	InventoryManagerComponent = CreateDefaultSubobject<UInventoryManagerComponent>(TEXT("Inventory Manager Component"));
}

void APlayerTankPawn::BeginPlay()
{
	Super::BeginPlay();

	InventoryComponent->Init();
	InventoryManagerComponent->SetBaseInventory(InventoryComponent);

	InventoryEquipComponent->Init();
	InventoryManagerComponent->SetBaseEquipment(InventoryEquipComponent);
}

void APlayerTankPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PerformMove(DeltaTime);
	PerformRotate(DeltaTime);
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

UInventoryManagerComponent* APlayerTankPawn::GetInventoryManager()
{
	return InventoryManagerComponent;
}

void APlayerTankPawn::EquipItem(EItemEquipSlot Slot, FName ItemID)
{
	const auto Component = GetEquipComponent(Slot);
	if (!Component) return;

	const auto ItemInfo = InventoryManagerComponent->GetItemData(ItemID);
	Component->SetStaticMesh(ItemInfo->Mesh.LoadSynchronous());
	Component->SetHiddenInGame(false);

	// Add advanced stats
}

void APlayerTankPawn::UnEquipItem(EItemEquipSlot Slot, FName ItemID)
{
	const auto Component = GetEquipComponent(Slot);
	if (!Component) return;

	Component->SetStaticMesh(nullptr);
	Component->SetHiddenInGame(false);

	// Remove advanced stats
}

UStaticMeshComponent* APlayerTankPawn::GetEquipComponent(EItemEquipSlot Slot)
{
	FName EquipTag = "";

	switch (Slot)
	{
	case EItemEquipSlot::Weapon: EquipTag = "Equip_Weapon";
		break;
	case EItemEquipSlot::Wheels: EquipTag = "Equip_Wheels";
		break;
	case EItemEquipSlot::Armor: EquipTag = "Equip_Armor";
		break;
	case EItemEquipSlot::None: break;
	default: return nullptr;
	}

	auto Components = GetComponentsByTag(UStaticMeshComponent::StaticClass(), EquipTag);
	return Components.Num() > 0 ? Cast<UStaticMeshComponent>(Components[0]) : nullptr;
}
