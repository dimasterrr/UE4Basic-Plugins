#include "SRadioButtonGroup.h"

#include "SlateOptMacros.h"

BEGIN_SLATE_FUNCTION_BUILD_OPTIMIZATION

void SRadioButtonGroup::Construct(const FArguments& InArgs)
{
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
	[
		SNew(STextBlock)
		.Text(FText::FromString(InText))
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

END_SLATE_FUNCTION_BUILD_OPTIMIZATION
