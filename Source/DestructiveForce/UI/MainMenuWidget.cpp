#include "MainMenuWidget.h"

#include "MainMenuSettingsWidget.h"
#include "Animation/UMGSequencePlayer.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Kismet/KismetSystemLibrary.h"

void UMainMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (NewGameButton)
	{
		NewGameButton->OnPressed.AddDynamic(this, &UMainMenuWidget::OnNewGameButtonClicked);
	}

	if (SettingsButton)
	{
		SettingsButton->OnPressed.AddDynamic(this, &UMainMenuWidget::OnSettingsButtonClicked);
	}

	if (ExitButton)
	{
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

	// TODO: Add Open level
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
