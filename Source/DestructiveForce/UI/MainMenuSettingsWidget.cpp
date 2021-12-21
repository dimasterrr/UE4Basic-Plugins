#include "MainMenuSettingsWidget.h"

#include "GeneralStyleSet.h"
#include "Components/Button.h"
#include "Components/CheckBox.h"
#include "Components/NativeWidgetHost.h"
#include "Components/RadioButtonGroup.h"
#include "Components/TextBlock.h"

void UMainMenuSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GeneralStyle = FGeneralStyleSet::Get().GetWidgetStyle<FGeneralStyle>(GeneralStylePresetName);

	if (BackButton)
	{
		BackButton->SetStyle(GeneralStyle.ButtonStyle);
		BackButton->OnPressed.AddDynamic(this, &UMainMenuSettingsWidget::OnBackButtonClicked);
	}

	if (ResolutionTextBlock)
	{
		ResolutionTextBlock->SetColorAndOpacity(GeneralStyle.TextBlockStyle.ColorAndOpacity);
		ResolutionTextBlock->SetFont(GeneralStyle.TextBlockStyle.Font);
	}

	if (ResolutionComboBox)
	{
		ResolutionComboBox->WidgetStyle = GeneralStyle.ComboBoxStyle;
	}

	if (QualityTextBlock)
	{
		QualityTextBlock->SetColorAndOpacity(GeneralStyle.TextBlockStyle.ColorAndOpacity);
		QualityTextBlock->SetFont(GeneralStyle.TextBlockStyle.Font);
	}

	if (QualityComboBox)
	{
		QualityComboBox->WidgetStyle = GeneralStyle.ComboBoxStyle;
	}

	if (LanguageTextBlock)
	{
		LanguageTextBlock->SetColorAndOpacity(GeneralStyle.TextBlockStyle.ColorAndOpacity);
		LanguageTextBlock->SetFont(GeneralStyle.TextBlockStyle.Font);
	}

	if (LanguageRadioButtonGroup)
	{
		LanguageRadioButtonGroup->WidgetStyle = GeneralStyle.RadioButtonGroupStyle;
		LanguageRadioButtonGroup->OnRadioButtonGroupChanged.AddDynamic(
			this, &UMainMenuSettingsWidget::OnRadioButtonGroupChanged);
	}

	if (SoundTextBlock)
	{
		SoundTextBlock->SetColorAndOpacity(GeneralStyle.TextBlockStyle.ColorAndOpacity);
		SoundTextBlock->SetFont(GeneralStyle.TextBlockStyle.Font);
	}

	if (SoundCheckBox)
	{
		SoundCheckBox->WidgetStyle = GeneralStyle.CheckBoxStyle;
	}
}

void UMainMenuSettingsWidget::OnBackButtonClicked()
{
	BackButtonClicked.Broadcast();
}

void UMainMenuSettingsWidget::OnRadioButtonGroupChanged(const int32 NewSelectedIndex)
{
}
