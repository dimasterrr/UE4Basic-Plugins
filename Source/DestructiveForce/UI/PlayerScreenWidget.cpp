#include "PlayerScreenWidget.h"

#include "Components/ProgressBar.h"

void UPlayerScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

UMinimapWidget* UPlayerScreenWidget::GetMinimap() const
{
	return PlayerMinimap;
}
