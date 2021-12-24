#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PlayerHUD.generated.h"

UENUM()
enum class EWidgetID : uint8
{
	MainMenu,
	PlayerScreen,
	GameOver,
	Inventory
};

UCLASS()
class DESTRUCTIVEFORCE_API APlayerHUD : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TMap<EWidgetID, TSubclassOf<UUserWidget>> WidgetClasses;

	UPROPERTY(BlueprintReadOnly)
	UUserWidget* CurrentWidget;

	UPROPERTY(BlueprintReadOnly)
	EWidgetID CurrentWidgetID;
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(BlueprintCallable)
	UUserWidget* CreateWidgetByClass(const TSubclassOf<UUserWidget> WidgetClass, const int32 ZOrder = 0);

public:
	APlayerHUD();

	virtual void Tick(float DeltaSeconds) override;

	UFUNCTION(BlueprintCallable)
	UUserWidget* ShowWidget(EWidgetID WidgetID, const int32 ZOrder = 0);

	UFUNCTION(BlueprintCallable)
	void HideWidget();

	UFUNCTION(BlueprintPure)
	UUserWidget* GetCurrentWidget() const;

	template<class T = UUserWidget>
	T* GetCurrentWidget() const;
};
