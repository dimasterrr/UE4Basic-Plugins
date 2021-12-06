#include "MinimapWidget.h"

TSharedRef<SWidget> UMinimapWidget::RebuildWidget()
{
	Minimap = SNew(SMinimap);
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

	if (Minimap.IsValid())
	{
		Minimap->SetupTextures(MinimapBackgroundTexture, PlayerIconTexture);
	}
}

void UMinimapWidget::UpdatePlayerPosition(const FVector2D& InPosition)
{
	if (Minimap.IsValid())
	{
		Minimap->UpdatePlayerPosition(InPosition);
	}
}
