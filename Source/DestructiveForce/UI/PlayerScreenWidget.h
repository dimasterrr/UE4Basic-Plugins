#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerScreenWidget.generated.h"

class UMinimapWidget;
class UProgressBar;

UCLASS()
class DESTRUCTIVEFORCE_API UPlayerScreenWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UProgressBar* AmmoProgressBar;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UMinimapWidget* PlayerMinimap;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION(BlueprintPure)
	UMinimapWidget* GetMinimap() const;
};
