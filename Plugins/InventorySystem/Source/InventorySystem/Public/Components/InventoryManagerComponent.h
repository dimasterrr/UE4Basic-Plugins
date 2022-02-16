#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventoryManagerComponent.generated.h"

class UInventoryMainWidget;
class UInventoryCellWidget;
struct FInventoryItemInfo;
class UInventoryWidget;
class UInventoryComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class INVENTORYSYSTEM_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	// Inventory module
	UPROPERTY()
	UInventoryComponent* SelfInventoryComponent;

	UPROPERTY()
	UInventoryComponent* SelfInventoryEquipComponent;

	UPROPERTY()
	UInventoryMainWidget* SelfInventoryWidget;

	// General
	UPROPERTY(EditAnywhere)
	UDataTable* InventoryItemsData;

	UPROPERTY(EditAnywhere)
	int32 MinSize = 20;

protected:
	void OnItemDropEvent(UInventoryCellWidget* From, UInventoryCellWidget* To);

public:
	void SetBaseInventory(UInventoryComponent* InventoryComponent);
	void SetBaseEquipment(UInventoryComponent* InventoryComponent);

	void PrepareInventoryWidget(UInventoryMainWidget* Widget);

	const FInventoryItemInfo* GetItemData(const FName& Id) const;
};
