#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DamageTaker.generated.h"

USTRUCT()
struct FDamageData
{
	GENERATED_BODY()

	UPROPERTY()
	float Damage;

	UPROPERTY()
	AActor* Instigator = nullptr;
};

UINTERFACE()
class UDamageTaker : public UInterface
{
	GENERATED_BODY()
};

class DESTRUCTIVEFORCE_API IDamageTaker
{
	GENERATED_BODY()

public:

	virtual void TakeDamage(const FDamageData& Data) = 0;
};
