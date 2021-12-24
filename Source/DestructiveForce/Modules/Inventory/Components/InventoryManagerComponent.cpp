#include "InventoryManagerComponent.h"

#include "InventoryComponent.h"
#include "Inventory/InventoryWidget.h"
#include "Blueprint/UserWidget.h"
#include "Inventory/InventoryCellWidget.h"

void UInventoryManagerComponent::Init(UInventoryComponent* InventoryComponent)
{
	SelfInventoryComponent = InventoryComponent;
}

void UInventoryManagerComponent::PrepareWidget(UInventoryWidget* Widget)
{
	if (!SelfInventoryComponent || !InventoryItemsData || !Widget) return;
	SelfInventoryWidget = Widget;
	SelfInventoryWidget->Init(FMath::Max(SelfInventoryComponent->GetItemsNum(), MinSize));
	SelfInventoryWidget->OnItemDrop.AddUObject(this, &UInventoryManagerComponent::OnItemDropEvent);

	for (auto& Item : SelfInventoryComponent->GetItems())
	{
		const auto ItemData = GetItemData(Item.Value.Id);
		if (!ItemData) continue;

		SelfInventoryWidget->AddItem(Item.Value, *ItemData, Item.Key);
	}
}

const FInventoryItemInfo* UInventoryManagerComponent::GetItemData(const FName& Id) const
{
	return InventoryItemsData ? InventoryItemsData->FindRow<FInventoryItemInfo>(Id, "") : nullptr;
}

void UInventoryManagerComponent::OnItemDropEvent(UInventoryCellWidget* From, UInventoryCellWidget* To)
{
	const auto FromItem = From->GetItem();
	const auto ToItem = To->GetItem();

	From->Erase();
	To->Erase();

	To->AddItem(FromItem, *GetItemData(FromItem.Id));
	if (ToItem.Id != NAME_None)
	{
		From->AddItem(ToItem, *GetItemData(ToItem.Id));
	}
}
