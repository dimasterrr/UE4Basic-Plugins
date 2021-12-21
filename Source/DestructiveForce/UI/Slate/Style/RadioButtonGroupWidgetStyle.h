#pragma once

#include "CoreMinimal.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "RadioButtonGroupWidgetStyle.generated.h"

USTRUCT()
struct DESTRUCTIVEFORCE_API FRadioButtonGroupStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FRadioButtonGroupStyle();
	virtual ~FRadioButtonGroupStyle();

	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FRadioButtonGroupStyle& GetDefault();

public:
	UPROPERTY(EditAnywhere, Category="Appearance")
	FCheckBoxStyle CheckBoxStyle;

	UPROPERTY(EditAnywhere, Category="Appearance")
	FTextBlockStyle TextBlockStyle;
};

UCLASS(hidecategories=Object, MinimalAPI)
class URadioButtonGroupWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FRadioButtonGroupStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&WidgetStyle);
	}
};
