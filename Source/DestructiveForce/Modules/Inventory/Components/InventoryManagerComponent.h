#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Engine/DataTable.h"
#include "InventoryManagerComponent.generated.h"

class UInventoryWidget;
class UInventoryComponent;
struct FInventoryItemInfo;

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

public:
	UInventoryManagerComponent();

	void Init(UInventoryComponent* InventoryComponent);

	FInventoryItemInfo* GetItemData(const FName Id) const;

	void PrepareWidget(UInventoryWidget* Widget);
};
