#pragma once

#include "CoreMinimal.h"
#include "GeneralWidgetStyle.h"
#include "Blueprint/UserWidget.h"
#include "Components/ComboBoxString.h"
#include "MainMenuSettingsWidget.generated.h"

class URadioButtonGroup;
class UNativeWidgetHost;
class UButton;
class ComboBoxString;
class UCheckBox;
class UTextBlock;

UCLASS()
class DESTRUCTIVEFORCE_API UMainMenuSettingsWidget : public UUserWidget
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE(FButtonClicked);

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UButton* BackButton;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ResolutionTextBlock;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UComboBoxString* ResolutionComboBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* QualityTextBlock;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UComboBoxString* QualityComboBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* LanguageTextBlock;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	URadioButtonGroup* LanguageRadioButtonGroup;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* SoundTextBlock;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UCheckBox* SoundCheckBox;

	// Style
	UPROPERTY(EditAnywhere, Category = "Appearance")
	FName GeneralStylePresetName = FName("GeneralDefault");
	
	UPROPERTY(EditAnywhere, Category = "Appearance")
	FGeneralStyle GeneralStyle;

public:
	UPROPERTY()
	FButtonClicked BackButtonClicked;

protected:
	virtual void NativeConstruct() override;

	UFUNCTION(BlueprintCallable)
	void OnBackButtonClicked();

	UFUNCTION(BlueprintCallable)
	void OnRadioButtonGroupChanged(const int32 NewSelectedIndex);
};
