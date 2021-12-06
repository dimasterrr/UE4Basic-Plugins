#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenuSettingsWidget.generated.h"

class URadioButtonGroup;
class UNativeWidgetHost;
class UButton;

UCLASS()
class DESTRUCTIVEFORCE_API UMainMenuSettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FBackButtonClicked);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* BackButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	URadioButtonGroup* RadioButtonGroupSettings;

public:
	UPROPERTY()
	FBackButtonClicked BackButtonClicked;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnBackButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnRadioButtonGroupChanged(const int32 NewSelectedIndex);
};
