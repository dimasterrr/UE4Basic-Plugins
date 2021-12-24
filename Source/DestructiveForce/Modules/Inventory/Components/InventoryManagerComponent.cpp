#include "InventoryManagerComponent.h"

#include "InventoryComponent.h"
#include "Inventory/InventoryWidget.h"
#include "Blueprint/UserWidget.h"

UInventoryManagerComponent::UInventoryManagerComponent()
{
}

void UInventoryManagerComponent::Init(UInventoryComponent* InventoryComponent)
{
	SelfInventoryComponent = InventoryComponent;
	if (!SelfInventoryComponent || !InventoryItemsData) return;
}

FInventoryItemInfo* UInventoryManagerComponent::GetItemData(const FName Id) const
{
	return InventoryItemsData ? InventoryItemsData->FindRow<FInventoryItemInfo>(Id, "") : nullptr;
}

void UInventoryManagerComponent::PrepareWidget(UInventoryWidget* Widget)
{
	if (!Widget) return;
	SelfInventoryWidget = Widget;
	
	const auto InventoryMinSize = FMath::Max(SelfInventoryComponent->GetItemsNum(), MinSize);
	Widget->Init(InventoryMinSize);
	
	for (auto& Item : SelfInventoryComponent->GetItems())
	{
		const auto ItemData = GetItemData(Item.Value.Id);
		if (!ItemData) continue;
	
		ItemData->Icon.LoadSynchronous();
		SelfInventoryWidget->AddItem(Item.Value, *ItemData, Item.Key);
	}
}
