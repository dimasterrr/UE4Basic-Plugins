#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PawnHealthBarWidget.generated.h"

class UProgressBar;
class UTextBlock;

UCLASS()
class DESTRUCTIVEFORCE_API UPawnHealthBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UProgressBar* HealthProgressBar;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* HealthPercentageText;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintCallable)
	void SetHealth(const float Health);
};
