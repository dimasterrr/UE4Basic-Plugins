#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Modules/Inventory/InventoryItem.h"
#include "InventoryWidget.generated.h"

class UTextBlock;
class UInventoryCellWidget;
class UUniformGridPanel;

UCLASS()
class DESTRUCTIVEFORCE_API UInventoryWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(meta=(BindWidgetOptional))
	UUniformGridPanel* ItemsGridPanel;

	UPROPERTY(meta=(BindWidgetOptional))
	UInventoryCellWidget* MoneyCellWidget;

	UPROPERTY(EditDefaultsOnly)
	int32 RowSize = 5;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryCellWidget> CellWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	TArray<UInventoryCellWidget*> CellWidgets;

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;

	UInventoryCellWidget* CreateCellWidget();

public:
	void Init(int32 ItemSize);

	UFUNCTION(BlueprintCallable)
	bool AddItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo, int32 SlotPosition = -1);

	UFUNCTION(BlueprintCallable)
	bool AddCurrencySlot(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo);
};
