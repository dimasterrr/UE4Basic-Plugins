#include "SRadioButtonGroup.h"

#include "SlateOptMacros.h"
#include "Style/RadioButtonGroupWidgetStyle.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SRadioButtonGroup::Construct(const FArguments& InArgs)
{
	SetRadioButtonGroupWidgetStyle(InArgs._Style);

	OnRadioButtonChanged = InArgs._OnRadioButtonChanged;

	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot()
		[
			CreateCheckbox(0, TEXT("Option 0"))
		]
		+ SVerticalBox::Slot()
		[
			CreateCheckbox(1, TEXT("Option 1"))
		]
		+ SVerticalBox::Slot()
		[
			CreateCheckbox(2, TEXT("Option 2"))
		]
	];
}

TSharedRef<SWidget> SRadioButtonGroup::CreateCheckbox(const int32 InIndex, const FString InText)
{
	return SNew(SCheckBox)
	.IsChecked_Raw(this, &SRadioButtonGroup::IsChecked, InIndex)
	.OnCheckStateChanged_Raw(this, &SRadioButtonGroup::OnCheckboxStateChanged, InIndex)
	.Style(CheckBoxStyle)
	[
		SNew(STextBlock)
		.Text(FText::FromString(InText))
		.TextStyle(TextBlockStyle)
	];
}

ECheckBoxState SRadioButtonGroup::IsChecked(int32 InIndex) const
{
	return InIndex == CurrentIndex ? ECheckBoxState::Checked : ECheckBoxState::Unchecked;
}

void SRadioButtonGroup::OnCheckboxStateChanged(const ECheckBoxState NewState, const int32 InIndex)
{
	if (NewState != ECheckBoxState::Checked) return;

	CurrentIndex = InIndex;
	OnRadioButtonChanged.ExecuteIfBound(CurrentIndex);
}

void SRadioButtonGroup::SetRadioButtonGroupWidgetStyle(const FRadioButtonGroupStyle* InStyle)
{
	CheckBoxStyle = &InStyle->CheckBoxStyle;
	TextBlockStyle = &InStyle->TextBlockStyle;
}

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
