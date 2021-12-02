#include "MainMenuSettingsWidget.h"
#include "Components/Button.h"

void UMainMenuSettingsWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (BackButton)
	{
		BackButton->OnPressed.AddDynamic(this, &UMainMenuSettingsWidget::OnBackButtonClicked);
	}
}

void UMainMenuSettingsWidget::OnBackButtonClicked()
{
	BackButtonClicked.Broadcast();
}
