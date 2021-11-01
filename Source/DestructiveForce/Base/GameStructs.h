#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameStructs.generated.h"

UENUM()
enum class EWeaponFireType
{
	Projectile UMETA(DisplayName = "Use Projectile"),
	Trace UMETA(DisplayName = "Use LineTrace"),
};

UCLASS()
class DESTRUCTIVEFORCE_API UGameStructs : public UObject
{
	GENERATED_BODY()
};