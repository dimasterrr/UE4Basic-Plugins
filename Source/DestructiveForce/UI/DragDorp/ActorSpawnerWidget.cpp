#include "ActorSpawnerWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Controllers/TankPlayerController.h"
#include "Kismet/GameplayStatics.h"

void UActorSpawnerWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ObjectNameTextBlock)
	{
		ObjectNameTextBlock->SetText(FText::FromName(ObjectName));
	}

	if (ObjectIconImage && ObjectIcon)
	{
		ObjectIconImage->Brush.SetResourceObject(ObjectIcon);
	}
}

void UActorSpawnerWidget::NativeConstruct()
{
	Super::NativeConstruct();

	PlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);

	if (const auto PController = Cast<ATankPlayerController>(PlayerController))
	{
		PController->OnLeftMouseButtonUp.AddUObject(this, &UActorSpawnerWidget::OnLeftMouseButtonDown);
	}
}

void UActorSpawnerWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);

	if (SpawnedActor && PlayerController)
	{
		FVector WorldMousePosition;
		FVector WorldMouseDirection;
		PlayerController->DeprojectMousePositionToWorld(WorldMousePosition, WorldMouseDirection);

		FCollisionQueryParams Params;
		Params.AddIgnoredActor(SpawnedActor);
		Params.AddIgnoredActor(PlayerController->GetPawn());

		FHitResult HitResult;
		GetWorld()->LineTraceSingleByChannel(HitResult, WorldMousePosition, WorldMouseDirection * 10000.f,
		                                     ECC_WorldStatic, Params);

		if (HitResult.bBlockingHit)
		{
			SpawnedActor->SetActorLocation(HitResult.Location);
		}
	}
}

FReply UActorSpawnerWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		FActorSpawnParameters Params;
		Params.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		Params.Instigator = PlayerController->GetPawn();

		SpawnedActor = GetWorld()->SpawnActor<AActor>(SpawningClass, Params);
	}

	return FReply::Handled();
}

void UActorSpawnerWidget::OnLeftMouseButtonDown()
{
	SpawnedActor = nullptr;
}
