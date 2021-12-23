#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ActorSpawnerWidget.generated.h"

class UImage;
class UTextBlock;
UCLASS()
class DESTRUCTIVEFORCE_API UActorSpawnerWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	AActor* SpawnedActor = nullptr;
	APlayerController* PlayerController;

protected:
	// Components
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* ObjectNameTextBlock;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UImage* ObjectIconImage;

	// Settings
	UPROPERTY(EditAnywhere, Category="Settings")
	FName ObjectName;

	UPROPERTY(EditAnywhere, Category="Settings")
	UTexture2D* ObjectIcon;

public:
	UPROPERTY(EditAnywhere)
	TSubclassOf<AActor> SpawningClass;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	void OnLeftMouseButtonDown();
};
