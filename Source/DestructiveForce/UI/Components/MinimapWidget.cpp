#include "MinimapWidget.h"

TSharedRef<SWidget> UMinimapWidget::RebuildWidget()
{
	Minimap = SNew(SMinimap)
		.Style(&WidgetStyle);
	return Minimap.ToSharedRef();
}

void UMinimapWidget::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);
	Minimap.Reset();
}

void UMinimapWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();
}

void UMinimapWidget::UpdatePlayerPosition(const FVector2D& InPosition)
{
	if (Minimap.IsValid())
	{
		Minimap->UpdatePlayerPosition(InPosition);
	}
}
