#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerScreenWidget.generated.h"

class UProgressBar;

UCLASS()
class DESTRUCTIVEFORCE_API UPlayerScreenWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UProgressBar* AmmoProgressBar;

protected:
	virtual void NativeConstruct() override;

public:
};
