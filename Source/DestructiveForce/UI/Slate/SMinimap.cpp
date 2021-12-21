#include "SMinimap.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SMinimap::Construct(const FArguments& InArgs)
{
	BackgroundBrush = &InArgs._Style->BackgroundBrush;
	PlayerBrush = &InArgs._Style->PlayerBrush;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION

int32 SMinimap::OnPaint(const FPaintArgs& Args, const FGeometry& AllottedGeometry, const FSlateRect& MyCullingRect,
                        FSlateWindowElementList& OutDrawElements, int32 LayerId, const FWidgetStyle& InWidgetStyle,
                        bool bParentEnabled) const
{
	// Base settings
	const auto DefaultMinimapSize = FVector2D(256.f);
	const auto MinimapScale = (AllottedGeometry.GetLocalSize() / DefaultMinimapSize).GetMin();
	const auto ScaledMinimapSize = DefaultMinimapSize * MinimapScale;
	// Base settings

	// Draw Minimap Background
	{
		const auto bIsEnabled = ShouldBeEnabled(bParentEnabled);
		const auto DrawEffects = bIsEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(ScaledMinimapSize, FSlateLayoutTransform()),
			BackgroundBrush,
			DrawEffects
		);
	}
	// Draw Minimap Background

	++LayerId; // Move To NextLayer

	// Draw Player Icon
	{
		constexpr auto PlayerIconScale = 1.f;
		const auto PlayerIconSize = FVector2D(50.f);
		const auto PlayerIconCenter = PlayerIconSize * 0.5f;
		const auto PlayerIconTranslation = ScaledMinimapSize * 0.5f - PlayerIconCenter + PlayerPosition;
		const auto PlayerIconTransform = FSlateLayoutTransform(PlayerIconScale, PlayerIconTranslation);

		const auto bIsEnabled = ShouldBeEnabled(bParentEnabled);
		const auto DrawEffects = bIsEnabled ? ESlateDrawEffect::None : ESlateDrawEffect::DisabledEffect;

		FSlateDrawElement::MakeBox(
			OutDrawElements,
			LayerId,
			AllottedGeometry.ToPaintGeometry(PlayerIconSize, PlayerIconTransform),
			PlayerBrush,
			DrawEffects
		);
	}
	// Draw Player Icon

	return SCompoundWidget::OnPaint(Args, AllottedGeometry, MyCullingRect, OutDrawElements, LayerId, InWidgetStyle,
	                                bParentEnabled);
}

void SMinimap::UpdatePlayerPosition(const FVector2D& InPosition)
{
	// TODO: Need calculate dynamic level size
	constexpr float WorldToTextureRatio = 256.f / 1500.f;
	const auto AdjustedPosition = FVector2D(InPosition.Y, -InPosition.X);

	PlayerPosition = AdjustedPosition * WorldToTextureRatio;
}
