#include "InventoryEquipComponent.h"

UInventoryEquipComponent::UInventoryEquipComponent()
{
	EquipSlots.Add(0, EItemEquipSlot::Wheels);
	EquipSlots.Add(1, EItemEquipSlot::Weapon);
	EquipSlots.Add(2, EItemEquipSlot::Armor);
}

int32 UInventoryEquipComponent::GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& Item) const
{
	if (Item.Type != EItemType::Equipment || 
		!EquipSlots.Contains(SlotIndex) || 
		EquipSlots.FindChecked(SlotIndex) != Item.EquipSlot)
	{
		return 0;
	}

	return 1;

	// return Item.Type != EItemType::Equipment
	       // || !EquipSlots.Contains(SlotIndex)
	       // || EquipSlots.FindChecked(SlotIndex) != Item.EquipSlot
		       // ? 0
		       // : 1;
}
