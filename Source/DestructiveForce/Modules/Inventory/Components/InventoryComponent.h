#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Modules/Inventory/InventoryItem.h"
#include "InventoryComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DESTRUCTIVEFORCE_API UInventoryComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TMap<int32, FInventorySlotInfo> Items;

public:
	FInventorySlotInfo* GetItem(int32 SlotIndex);
	void SetItem(int32 SlotIndex, const FInventorySlotInfo& Item);
	
	void ClearItem(int32 SlotIndex);
	void CLearAll();

	const TMap<int32, FInventorySlotInfo>& GetItems() const;
	int32 GetItemsNum() const;
};
