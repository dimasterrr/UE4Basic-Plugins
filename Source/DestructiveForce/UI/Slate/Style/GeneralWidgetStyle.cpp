#include "GeneralWidgetStyle.h"

FGeneralStyle::FGeneralStyle()
{
	CheckBoxStyle = FCoreStyle::Get().GetWidgetStyle<FCheckBoxStyle>(TEXT("Checkbox"));
	TextBlockStyle = FCoreStyle::Get().GetWidgetStyle<FTextBlockStyle>(TEXT("NormalText"));
	ComboBoxStyle = FCoreStyle::Get().GetWidgetStyle<FComboBoxStyle>(TEXT("Combbox"));
	ButtonStyle = FCoreStyle::Get().GetWidgetStyle<FButtonStyle>(TEXT("Button"));
	RadioButtonGroupStyle = FCoreStyle::Get().GetWidgetStyle<FRadioButtonGroupStyle>(TEXT("RadioButtonGroup"));
}

FGeneralStyle::~FGeneralStyle()
{
}

const FName FGeneralStyle::TypeName(TEXT("FGeneralStyle"));

const FGeneralStyle& FGeneralStyle::GetDefault()
{
	static FGeneralStyle Default;
	return Default;
}

void FGeneralStyle::GetResources(TArray<const FSlateBrush*>& OutBrushes) const
{
}
