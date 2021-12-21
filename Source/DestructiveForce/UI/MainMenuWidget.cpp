#include "MainMenuWidget.h"

#include "GeneralStyleSet.h"
#include "MainMenuSettingsWidget.h"
#include "Animation/UMGSequencePlayer.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	GeneralStyle = FGeneralStyleSet::Get().GetWidgetStyle<FGeneralStyle>(GeneralStylePresetName);

	if (NewGameButton)
	{
		NewGameButton->SetStyle(GeneralStyle.ButtonStyle);
		NewGameButton->OnPressed.AddDynamic(this, &UMainMenuWidget::OnNewGameButtonClicked);
	}

	if (SettingsButton)
	{
		SettingsButton->SetStyle(GeneralStyle.ButtonStyle);
		SettingsButton->OnPressed.AddDynamic(this, &UMainMenuWidget::OnSettingsButtonClicked);
	}

	if (ExitButton)
	{
		ExitButton->SetStyle(GeneralStyle.ButtonStyle);
		ExitButton->OnPressed.AddDynamic(this, &UMainMenuWidget::OnExitButtonClicked);
	}

	if (SettingsWidget)
	{
		SettingsWidget->BackButtonClicked.AddDynamic(this, &UMainMenuWidget::OnBackToMainScreen);
	}

	if (ShowWidgetAnimation)
	{
		FWidgetAnimationDynamicEvent AnimationEvent;
		AnimationEvent.BindDynamic(this, & UMainMenuWidget::OnShowWidgetAnimationFinished);
		BindToAnimationFinished(ShowWidgetAnimation, AnimationEvent);
	}

	if (HideWidgetAnimation)
	{
		FWidgetAnimationDynamicEvent AnimationEvent;
		AnimationEvent.BindDynamic(this, & UMainMenuWidget::OnHideWidgetAnimationFinished);
		BindToAnimationFinished(HideWidgetAnimation, AnimationEvent);
	}
}

void UMainMenuWidget::OnNewGameButtonClicked()
{
	if (IsActionsLocker) return;

	UGameplayStatics::OpenLevel(this, *NewLevel.GetAssetName());
}

void UMainMenuWidget::OnSettingsButtonClicked()
{
	if (IsActionsLocker) return;

	SwitchWidget(1);
}

void UMainMenuWidget::OnExitButtonClicked()
{
	if (IsActionsLocker) return;

	UKismetSystemLibrary::QuitGame(GetWorld(),
	                               GetWorld()->GetFirstPlayerController(),
	                               EQuitPreference::Quit,
	                               true);
}

void UMainMenuWidget::OnBackToMainScreen()
{
	if (IsActionsLocker) return;

	SwitchWidget(0);
}

void UMainMenuWidget::OnShowWidgetAnimationFinished()
{
	IsActionsLocker = false;
}

void UMainMenuWidget::OnHideWidgetAnimationFinished()
{
	WidgetSwitcher->SetActiveWidgetIndex(NextWidgetIndex);

	PlayAnimation(ShowWidgetAnimation);
}

void UMainMenuWidget::SwitchWidget(const int WidgetIndex)
{
	if (NextWidgetIndex == WidgetIndex) return;

	IsActionsLocker = true;
	NextWidgetIndex = WidgetIndex;

	PlayAnimation(HideWidgetAnimation);
}
