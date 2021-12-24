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
	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UUniformGridPanel* ItemsGridPanel;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidgetOptional))
	UInventoryCellWidget* MoneyCellWidget;

	UPROPERTY(BlueprintReadOnly)
	TArray<UInventoryCellWidget*> CellWidgets;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UInventoryCellWidget> CellWidgetClass;

	UPROPERTY(EditDefaultsOnly)
	int32 RowSize = 5;

public:
	FOnItemDrop OnItemDrop;

protected:
	UInventoryCellWidget* CreateCellWidget();

	void OnItemDropEvent(UInventoryCellWidget* From, UInventoryCellWidget* To);

	UFUNCTION(BlueprintCallable)
	void SetFilterByType(const TEnumAsByte<EItemType> Type);
	
public:
	UFUNCTION(BlueprintCallable)
	void Init(int32 GridSizeCount);

	UFUNCTION(BlueprintCallable)
	bool AddItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo, int32 SlotPosition);

	UFUNCTION(BlueprintCallable)
	bool AddCurrencySlot(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo);
};
