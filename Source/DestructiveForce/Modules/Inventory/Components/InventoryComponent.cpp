#include "InventoryComponent.h"

FInventorySlotInfo* UInventoryComponent::GetItem(int32 SlotIndex)
{
	return Items.Find(SlotIndex);
}

void UInventoryComponent::SetItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	ClearItem(SlotIndex);
	Items.Add(SlotIndex, Item);
}

void UInventoryComponent::ClearItem(int32 SlotIndex)
{
	Items.Remove(SlotIndex);
}

void UInventoryComponent::CLearAll()
{
	Items.Empty();
}

const TMap<int32, FInventorySlotInfo>& UInventoryComponent::GetItems() const
{
	return Items;
}

int32 UInventoryComponent::GetItemsNum() const
{
	return Items.Num();
}
