#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Modules/Inventory/InventoryItem.h"
#include "InventoryCellWidget.generated.h"

class UTextBlock;
class UImage;

UCLASS()
class DESTRUCTIVEFORCE_API UInventoryCellWidget : public UUserWidget
{
	GENERATED_BODY()

private:
	int32 IndexInInventory = INDEX_NONE;
	bool HasItem;
	FInventorySlotInfo StoredItem;

protected:
	UPROPERTY(meta=(BindWidgetOptional))
	UImage* ItemIconImage;

	UPROPERTY(meta=(BindWidgetOptional))
	UTextBlock* CountTextBlock;

public:
	UFUNCTION(BlueprintCallable)
	const FInventorySlotInfo& GetItem();

	UFUNCTION(BlueprintCallable)
	bool AddItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo);

	UFUNCTION(BlueprintCallable)
	void Erase();

	UFUNCTION(BlueprintPure)
	bool IsEmpty() const;

	// Helpers
	UFUNCTION(BlueprintCallable)
	void SetInventorySlotIndex(const int32 Index);

	UFUNCTION(BlueprintPure)
	int32 GetIndexInInventory() const;
};
