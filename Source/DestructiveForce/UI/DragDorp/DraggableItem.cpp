#include "DraggableItem.h"

#include "ObjectDragDropOperation.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"

void UDraggableItem::NativePreConstruct()
{
	Super::NativePreConstruct();

	if (ObjectNameTextBlock)
	{
		ObjectNameTextBlock->SetText(FText::FromName(ObjectName));
	}

	if (ObjectIconImage && ObjectIcon)
	{
		ObjectIconImage->Brush.SetResourceObject(ObjectIcon);
	}
}

FReply UDraggableItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.IsMouseButtonDown(EKeys::LeftMouseButton))
	{
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}

	return FReply::Handled();
}

void UDraggableItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
                                          UDragDropOperation*& OutOperation)
{
	OutOperation = UWidgetBlueprintLibrary::CreateDragDropOperation(UObjectDragDropOperation::StaticClass());

	if (const auto ObjectDragDropOperation = Cast<UObjectDragDropOperation>(OutOperation))
	{
		ObjectDragDropOperation->DefaultDragVisual = this;
		ObjectDragDropOperation->OnDragCancelled.AddDynamic(this, &UDraggableItem::RestoreWidgetStyles);

		SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, .7f));
		SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	}
	else
	{
		Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	}
}

bool UDraggableItem::NativeOnDragOver(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                      UDragDropOperation* InOperation)
{
	if (const auto ObjectDragDropOperation = Cast<UObjectDragDropOperation>(InOperation))
	{
		const auto ParentWidget = GetParent();
		if (const auto PanelWidget = Cast<UPanelWidget>(ParentWidget))
		{
			if (this != ObjectDragDropOperation->DefaultDragVisual)
			{
				const auto OverIndex = PanelWidget->GetChildIndex(ObjectDragDropOperation->DefaultDragVisual);
				
				if (OverIndex >= 0)
				{
					PanelWidget->RemoveChildAt(OverIndex);
					const auto SafeItems = PanelWidget->GetAllChildren();
					PanelWidget->ClearChildren();

					for (const auto& Item : SafeItems)
					{
						PanelWidget->AddChild(Item);
						if (Item == this) PanelWidget->AddChild(ObjectDragDropOperation->DefaultDragVisual);
					}
				}
			}
		}
	}

	return Super::NativeOnDragOver(InGeometry, InDragDropEvent, InOperation);
}

bool UDraggableItem::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
                                  UDragDropOperation* InOperation)
{
	if (InOperation && InOperation->DefaultDragVisual)
	{
		RestoreWidgetStyles(InOperation);
		return true;
	}
	return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
}

void UDraggableItem::RestoreWidgetStyles(UDragDropOperation* Operation)
{
	if (const auto ObjectDragDropOperation = Cast<UObjectDragDropOperation>(Operation))
	{
		SetColorAndOpacity(FLinearColor(1.f, 1.f, 1.f, 1.f));
		SetVisibility(ESlateVisibility::Visible);
	}
}
