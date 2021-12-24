#include "InventoryWidget.h"

#include "InventoryCellWidget.h"
#include "Components/TextBlock.h"
#include "Components/UniformGridPanel.h"

void UInventoryWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UInventoryWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

UInventoryCellWidget* UInventoryWidget::CreateCellWidget()
{
	if (!CellWidgetClass) return nullptr;

	const auto CellWidget = CreateWidget<UInventoryCellWidget>(this, CellWidgetClass);
	CellWidgets.Add(CellWidget);

	return CellWidget;
}

void UInventoryWidget::Init(int32 ItemSize)
{
	if (!ItemsGridPanel) return;

	ItemsGridPanel->ClearChildren();
	for (auto i = 0; i < ItemSize; ++i)
	{
		const auto CellWidget = CreateCellWidget();
		CellWidget->SetInventorySlotIndex(i);

		ItemsGridPanel->AddChildToUniformGrid(CellWidget, i / RowSize, i % RowSize);
	}
}

bool UInventoryWidget::AddItem(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo,
                               int32 SlotPosition)
{
	if (ItemInfo.Type == EItemType::Currency) return AddCurrencySlot(SlotInfo, ItemInfo);
	if (!ItemsGridPanel) return false;

	const auto FindPredicate = [SlotPosition](UInventoryCellWidget* Widget)
	{
		return Widget && Widget->GetIndexInInventory() == SlotPosition;
	};

	UInventoryCellWidget* WidgetToAddItem = nullptr;
	const auto WidgetToAddItemPtr = CellWidgets.FindByPredicate(FindPredicate);

	if (WidgetToAddItemPtr)
	{
		WidgetToAddItem = *WidgetToAddItemPtr;
	}
	else
	{
		for (const auto& CellWidget : CellWidgets)
		{
			if (!CellWidget->IsEmpty()) continue;

			WidgetToAddItem = CellWidget;
			break;
		}
	}

	if (!WidgetToAddItem) return false;
	return WidgetToAddItem->AddItem(SlotInfo, ItemInfo);
}

bool UInventoryWidget::AddCurrencySlot(const FInventorySlotInfo& SlotInfo, const FInventoryItemInfo& ItemInfo)
{
	if (!MoneyCellWidget) return false;

	return MoneyCellWidget->AddItem(SlotInfo, ItemInfo);
}
