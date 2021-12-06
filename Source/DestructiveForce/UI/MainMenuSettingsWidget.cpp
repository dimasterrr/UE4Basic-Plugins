#include "MainMenuSettingsWidget.h"
#include "Components/Button.h"
#include "Components/NativeWidgetHost.h"
#include "Components/RadioButtonGroup.h"
#include "Slate/SRadioButtonGroup.h"

void UMainMenuSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackButton)
	{
		BackButton->OnPressed.AddDynamic(this, &UMainMenuSettingsWidget::OnBackButtonClicked);
	}

	if (RadioButtonGroupSettings)
	{
		RadioButtonGroupSettings->OnRadioButtonGroupChanged.AddDynamic(this,
		                                                       &UMainMenuSettingsWidget::OnRadioButtonGroupChanged);
	}
}

void UMainMenuSettingsWidget::OnBackButtonClicked()
{
	BackButtonClicked.Broadcast();
}


void UMainMenuSettingsWidget::OnRadioButtonGroupChanged(const int32 NewSelectedIndex)
{
}
