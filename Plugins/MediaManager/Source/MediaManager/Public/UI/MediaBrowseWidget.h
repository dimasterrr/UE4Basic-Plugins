#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MediaBrowseWidget.generated.h"

class UImage;
class UMediaPlayer;
class UButton;

UCLASS()
class MEDIAMANAGER_API UMediaBrowseWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	UPROPERTY()
	UMaterialInstanceDynamic* MaterialInstanceDynamic;

protected:
	UPROPERTY(EditAnywhere)
	UMediaPlayer* MediaPlayer;

	UPROPERTY(EditAnywhere)
	class UMaterialInterface* Material;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UButton* BrowseButton;

	UPROPERTY(EditAnywhere, meta=(BindWidget))
	UImage* RenderImage;

protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void OnButtonPressed();

	UFUNCTION()
	void OnMediaOpened(FString Path);
};
