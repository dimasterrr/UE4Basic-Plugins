#include "InventoryEquipComponent.h"

#include "EquipInterface.h"

UInventoryEquipComponent::UInventoryEquipComponent()
{
	EquipSlots.Add(0, EItemEquipSlot::Wheels);
	EquipSlots.Add(1, EItemEquipSlot::Weapon);
	EquipSlots.Add(2, EItemEquipSlot::Armor);
}

int32 UInventoryEquipComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& Item) const
{
	return Item.Type != EItemType::Equipment
	       || !EquipSlots.Contains(SlotIndex)
	       || EquipSlots.FindChecked(SlotIndex) != Item.EquipSlot
		       ? 0
		       : 1;
}

void UInventoryEquipComponent::UpsertItem(int32 SlotIndex, const FInventorySlotInfo& Item)
{
	const auto InventoryOwner = Cast<IEquipInterface>(GetOwner());
	if (!InventoryOwner)
	{
		Super::UpsertItem(SlotIndex, Item);
		return;
	}

	const auto Slot = EquipSlots.Contains(SlotIndex) ? EquipSlots.FindChecked(SlotIndex) : EItemEquipSlot::None;

	if (const auto EquipItem = GetItem(SlotIndex))
	{
		InventoryOwner->UnEquipItem(Slot, EquipItem->Id);
	}

	Super::UpsertItem(SlotIndex, Item);
	InventoryOwner->EquipItem(Slot, Item.Id);
}

void UInventoryEquipComponent::RemoveItem(int32 SlotIndex)
{
	const auto InventoryOwner = Cast<IEquipInterface>(GetOwner());
	if (!InventoryOwner)
	{
		Super::RemoveItem(SlotIndex);
		return;
	}

	const auto Slot = EquipSlots.Contains(SlotIndex) ? EquipSlots.FindChecked(SlotIndex) : EItemEquipSlot::None;

	if (const auto EquipItem = GetItem(SlotIndex))
	{
		InventoryOwner->UnEquipItem(Slot, EquipItem->Id);
	}

	Super::RemoveItem(SlotIndex);
}
