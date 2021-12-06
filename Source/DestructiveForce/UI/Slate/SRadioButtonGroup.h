#pragma once

#include "CoreMinimal.h"
#include "Chaos/AABB.h"
#include "Chaos/AABB.h"
#include "Widgets/SCompoundWidget.h"

class DESTRUCTIVEFORCE_API SRadioButtonGroup : public SCompoundWidget
{
	DECLARE_DELEGATE_OneParam(FOnRadioButtonChanged, int32 /*New Slate Index*/)

private:
	int32 CurrentIndex = INDEX_NONE;

private:
	TSharedRef<SWidget> CreateCheckbox(const int32 InIndex, const FString InText);

	ECheckBoxState IsChecked(const int32 InIndex) const;

	void OnCheckboxStateChanged(const ECheckBoxState NewState, const int32 InIndex);

public:
	FOnRadioButtonChanged OnRadioButtonChanged;

public:
	SLATE_BEGIN_ARGS(SRadioButtonGroup)

		{
		}

		SLATE_EVENT(FOnRadioButtonChanged, OnRadioButtonChanged)

	SLATE_END_ARGS()


	void Construct(const FArguments& InArgs);
};
