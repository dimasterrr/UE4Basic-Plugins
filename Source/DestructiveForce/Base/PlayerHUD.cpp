#include "PlayerHUD.h"

#include "Blueprint/UserWidget.h"

APlayerHUD::APlayerHUD()
{
	PrimaryActorTick.bCanEverTick = true;
}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();
}

UUserWidget* APlayerHUD::CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder)
{
	const auto NewWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
	NewWidget->AddToViewport(ZOrder);

	return NewWidget;
}

UUserWidget* APlayerHUD::ShowWidget(const EWidgetID WidgetID, const int32 ZOrder)
{
	HideWidget();

	const auto WidgetClass = WidgetClasses.Find(WidgetID);
	if (WidgetClass && *WidgetClass)
	{
		CurrentWidget = CreateWidgetByClass(*WidgetClass, ZOrder);
	}

	return CurrentWidget;
}

void APlayerHUD::HideWidget()
{
	if (!CurrentWidget) return;

	CurrentWidget->RemoveFromParent();
	CurrentWidget = nullptr;
}

UUserWidget* APlayerHUD::GetCurrentWidget() const
{
	return CurrentWidget;
}

template <class T>
T* APlayerHUD::GetCurrentWidget() const
{
	return Cast<T>(CurrentWidget);
}
