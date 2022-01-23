#pragma once

#include "CoreMinimal.h"
#include "InventoryComponent.h"
#include "InventoryEquipComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DESTRUCTIVEFORCE_API UInventoryEquipComponent : public UInventoryComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere)
	TMap<int32, EItemEquipSlot> EquipSlots;
	
public:
	UInventoryEquipComponent();

	virtual int32 GetMaxItemAmount(int32 SlotIndex, const FInventoryItemInfo& Item) const override;
};
