#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "InventoryDragDropOperation.generated.h"

class UInventoryCellWidget;

UCLASS()
class DESTRUCTIVEFORCE_API UInventoryDragDropOperation : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	UPROPERTY()
	UInventoryCellWidget* SourceCell;
};
