#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

class DESTRUCTIVEFORCE_API SMinimap : public SCompoundWidget
{
protected:
	UTexture2D* MinimapBackgroundTexture = nullptr;
	UTexture2D* PlayerIconTexture = nullptr;

	FVector2D PlayerPosition;

public:
	SLATE_BEGIN_ARGS(SMinimap)
		{
		}

		SLATE_ARGUMENT(UTexture2D*, MinimapBackgroundTexture)
		SLATE_ARGUMENT(UTexture2D*, PlayerIconTexture)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	                      FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	                      bool bParentEnabled) const override;

	void SetupTextures(const UTexture2D* InMinimapBackgroundTexture, const UTexture2D* InPlayerIconTexture);

	void UpdatePlayerPosition(const FVector2D& InPosition);
};
