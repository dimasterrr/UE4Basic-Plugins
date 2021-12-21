#pragma once

#include "CoreMinimal.h"
#include "MinimapWidgetStyle.h"
#include "Widgets/SCompoundWidget.h"

class DESTRUCTIVEFORCE_API SMinimap : public SCompoundWidget
{
protected:
	const FSlateBrush* BackgroundBrush = nullptr;
	const FSlateBrush* PlayerBrush = nullptr;

	FVector2D PlayerPosition;

public:
	SLATE_BEGIN_ARGS(SMinimap)
		{
		}

		SLATE_STYLE_ARGUMENT(FMinimapStyle, Style)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	virtual int32 OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
	                      FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
	                      bool bParentEnabled) const override;

	void UpdatePlayerPosition(const FVector2D& InPosition);
};
