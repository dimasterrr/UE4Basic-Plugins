#include "InventoryCellWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"

const FInventorySlotInfo& UInventoryCellWidget::GetItem()
{
	return StoredItem;
}

bool UInventoryCellWidget::AddItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo)
{
	if (HasItem) return false;

	if (ItemIconImage)
	{
		ItemIconImage->SetBrushFromTexture(ItemInfo.Icon.Get());
		ItemIconImage->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
	}

	if (CountTextBlock)
	{
		CountTextBlock->SetText(FText::FromString(FString::FromInt(SlotInfo.Count)));
	}

	HasItem = true;
	StoredItem = SlotInfo;

	return true;
}

void UInventoryCellWidget::Erase()
{
	if (!HasItem) return;

	if (ItemIconImage)
	{
		ItemIconImage->SetBrush(FSlateBrush());
		ItemIconImage->SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 0.f));
	}

	if (CountTextBlock)
	{
		CountTextBlock->SetText(FText::FromString("0"));
	}

	HasItem = false;
	StoredItem = FInventorySlotInfo();
}

bool UInventoryCellWidget::IsEmpty() const
{
	return !HasItem;
}

void UInventoryCellWidget::SetInventorySlotIndex(const int32 Index)
{
	IndexInInventory = Index;
}

int32 UInventoryCellWidget::GetIndexInInventory() const
{
	return IndexInInventory;
}
