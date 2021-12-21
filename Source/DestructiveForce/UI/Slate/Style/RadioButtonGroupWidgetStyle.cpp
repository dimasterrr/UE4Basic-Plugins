#include "RadioButtonGroupWidgetStyle.h"

FRadioButtonGroupStyle::FRadioButtonGroupStyle()
{
	CheckBoxStyle = FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>(TEXT("Checkbox"));
	TextBlockStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>(TEXT("NormalText"));
}

FRadioButtonGroupStyle::~FRadioButtonGroupStyle()
{
}

const FName FRadioButtonGroupStyle::TypeName(TEXT("FRadioButtonGroupStyle"));

const FRadioButtonGroupStyle& FRadioButtonGroupStyle::GetDefault()
{
	static FRadioButtonGroupStyle Default;
	return Default;
}

void FRadioButtonGroupStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
}
