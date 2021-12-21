#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "MinimapWidgetStyle.generated.h"

USTRUCT()
struct DESTRUCTIVEFORCE_API FMinimapStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FMinimapStyle();
	virtual ~FMinimapStyle();

	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FMinimapStyle& GetDefault();

public:
	UPROPERTY(EditAnywhere, Category="Appearance")
	FSlateBrush BackgroundBrush;
	
	UPROPERTY(EditAnywhere, Category="Appearance")
	FSlateBrush PlayerBrush;
};

UCLASS(hidecategories=Object, MinimalAPI)
class UMinimapWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FMinimapStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&WidgetStyle);
	}
};
