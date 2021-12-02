#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuWidget.generated.h"

class UButton;
class UWidgetSwitcher;
class UMainMenuSettingsWidget;

UCLASS()
class DESTRUCTIVEFORCE_API UMainMenuWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	bool IsActionsLocker = false;
	int NextWidgetIndex = INDEX_NONE;

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UButton* NewGameButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* SettingsButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* ExitButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UWidgetSwitcher* WidgetSwitcher;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UMainMenuSettingsWidget* SettingsWidget;

	// Animations
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* ShowWidgetAnimation;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetAnim), Transient)
	UWidgetAnimation* HideWidgetAnimation;

private:
	UFUNCTION(BlueprintCallable)
	void OnShowWidgetAnimationFinished();

	UFUNCTION(BlueprintCallable)
	void OnHideWidgetAnimationFinished();

	UFUNCTION(BlueprintCallable)
	void SwitchWidget(const int WidgetIndex);

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnNewGameButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnSettingsButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnExitButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnBackToMainScreen();
};
