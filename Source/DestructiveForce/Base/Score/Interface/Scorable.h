#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Scorable.generated.h"

UINTERFACE()
class UScorable : public UInterface
{
	GENERATED_BODY()
};

class DESTRUCTIVEFORCE_API IScorable
{
	GENERATED_BODY()

public:
	virtual int GetDieScore() const = 0;
};
