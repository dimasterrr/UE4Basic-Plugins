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

	UPROPERTY(EditAnywhere)
	UDataTable* BaseInventorySet;

public:
	void Init();
	void SetupBaseInventorySet(UDataTable* InventorySet);

	FInventorySlotInfo* GetItem(int32 SlotIndex);
	void UpsertItem(int32 SlotIndex, const FInventorySlotInfo& Item);
	void RemoveItem(int32 SlotIndex);

	const TMap<int32, FInventorySlotInfo>& GetItems() const;
	int32 GetItemsNum() const;
	void RemoveAll();
};
