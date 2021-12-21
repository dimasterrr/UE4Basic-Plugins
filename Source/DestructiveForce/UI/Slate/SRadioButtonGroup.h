#pragma once

#include "CoreMinimal.h"
#include "Widgets/SCompoundWidget.h"

struct FRadioButtonGroupStyle;

class DESTRUCTIVEFORCE_API SRadioButtonGroup : public SCompoundWidget
{
	DECLARE_DELEGATE_OneParam(FOnRadioButtonChanged, int32 /*New Slate Index*/)

private:
	int32 CurrentIndex = INDEX_NONE;

private:
	TSharedRef<SWidget> CreateCheckbox(const int32 InIndex, const FString InText);

	ECheckBoxState IsChecked(const int32 InIndex) const;

	void OnCheckboxStateChanged(const ECheckBoxState NewState, const int32 InIndex);

protected:
	const FCheckBoxStyle* CheckBoxStyle = nullptr;
	const FTextBlockStyle* TextBlockStyle = nullptr;

public:
	FOnRadioButtonChanged OnRadioButtonChanged;

public:
	SLATE_BEGIN_ARGS(SRadioButtonGroup)

		{
		}

		SLATE_EVENT(FOnRadioButtonChanged, OnRadioButtonChanged)

		SLATE_STYLE_ARGUMENT(FRadioButtonGroupStyle, Style)

	SLATE_END_ARGS()

	void Construct(const FArguments& InArgs);

	void SetRadioButtonGroupWidgetStyle(const FRadioButtonGroupStyle* InStyle);
};
