#pragma once

#include "CoreMinimal.h"
#include "RadioButtonGroupWidgetStyle.h"
#include "Styling/SlateWidgetStyle.h"
#include "Styling/SlateWidgetStyleContainerBase.h"

#include "GeneralWidgetStyle.generated.h"

USTRUCT()
struct DESTRUCTIVEFORCE_API FGeneralStyle : public FSlateWidgetStyle
{
	GENERATED_USTRUCT_BODY()

	FGeneralStyle();
	virtual ~FGeneralStyle();

	virtual void GetResources(TArray<const FSlateBrush*>& OutBrushes) const override;
	static const FName TypeName;
	virtual const FName GetTypeName() const override { return TypeName; };
	static const FGeneralStyle& GetDefault();

public:
	UPROPERTY(EditAnywhere, Category="Appearance")
	FCheckBoxStyle CheckBoxStyle;

	UPROPERTY(EditAnywhere, Category="Appearance")
	FTextBlockStyle TextBlockStyle;

	UPROPERTY(EditAnywhere, Category="Appearance")
	FComboBoxStyle ComboBoxStyle;

	UPROPERTY(EditAnywhere, Category="Appearance")
	FButtonStyle ButtonStyle;

	UPROPERTY(EditAnywhere, Category="Appearance")
	FRadioButtonGroupStyle RadioButtonGroupStyle;
};

UCLASS(hidecategories=Object, MinimalAPI)
class UGeneralWidgetStyle : public USlateWidgetStyleContainerBase
{
	GENERATED_BODY()

public:
	UPROPERTY(Category=Appearance, EditAnywhere, meta=(ShowOnlyInnerProperties))
	FGeneralStyle WidgetStyle;

	virtual const struct FSlateWidgetStyle* const GetStyle() const override
	{
		return static_cast<const struct FSlateWidgetStyle*>(&WidgetStyle);
	}
};
