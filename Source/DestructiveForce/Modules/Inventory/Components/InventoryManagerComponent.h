#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventoryManagerComponent.generated.h"

class UInventoryCellWidget;
struct FInventoryItemInfo;
class UInventoryWidget;
class UInventoryComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DESTRUCTIVEFORCE_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY()
	UInventoryComponent* SelfInventoryComponent;

	UPROPERTY()
	UInventoryWidget* SelfInventoryWidget;

	UPROPERTY(EditAnywhere)
	UDataTable* InventoryItemsData;

	UPROPERTY(EditAnywhere)
	int32 MinSize = 20;

protected:
	void OnItemDropEvent(UInventoryCellWidget* From, UInventoryCellWidget* To);

public:
	void Init(UInventoryComponent* InventoryComponent);
	void PrepareWidget(UInventoryWidget* Widget);

	const FInventoryItemInfo* GetItemData(const FName& Id) const;
};
