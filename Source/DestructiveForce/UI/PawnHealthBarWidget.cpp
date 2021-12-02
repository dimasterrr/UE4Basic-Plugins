#include "PawnHealthBarWidget.h"

#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"

void UPawnHealthBarWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

void UPawnHealthBarWidget::SetHealth(const float Health)
{
	if (HealthProgressBar)
	{
		HealthProgressBar->SetPercent(Health / 100.f);
	}

	if (HealthPercentageText)
	{
		HealthPercentageText->SetText(FText::AsNumber(Health));
	}
}
