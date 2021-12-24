#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "InventoryItem.generated.h"


UENUM()
enum class EItemType : uint8
{
	Miscellaneous,
	Currency,
	Equipment,
	Consumable
};

UENUM()
enum class EItemRarity : uint8
{
	Common,
	Uncommon,
	Rare,
	Mythical,
	Legendary,
	Immortal
};

// DECLARE_MULTICAST_DELEGATE_TwoParams(FOnItemDrop, class UInventoryCellWidget* /*from*/, class UInventoryCellWidget* /*to*/)

USTRUCT(BlueprintType)
struct DESTRUCTIVEFORCE_API FInventoryItemInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	// General
	UPROPERTY(EditDefaultsOnly, Category="General")
	FName Id;

	UPROPERTY(EditDefaultsOnly, Category="General")
	FText Name;

	UPROPERTY(EditDefaultsOnly, Category="General")
	FText Description;

	// Type
	UPROPERTY(EditDefaultsOnly, Category="Type")
	EItemType Type;

	UPROPERTY(EditDefaultsOnly, Category="Type")
	EItemRarity Rarity;

	// View
	UPROPERTY(EditDefaultsOnly, Category="View")
	TSoftObjectPtr<UTexture2D> Icon;

	UPROPERTY(EditDefaultsOnly, Category="View")
	TSoftObjectPtr<UStaticMesh> Mesh;
};

USTRUCT(BlueprintType)
struct DESTRUCTIVEFORCE_API FInventorySlotInfo : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName Id;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 Count;
};
