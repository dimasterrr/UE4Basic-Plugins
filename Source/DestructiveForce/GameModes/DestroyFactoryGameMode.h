#pragma once

#include "CoreMinimal.h"
#include "DestructiveForce/Base/MainGameModeBase.h"
#include "DestroyFactoryGameMode.generated.h"

class ATankBuilder;
UCLASS()
class DESTRUCTIVEFORCE_API ADestroyFactoryGameMode : public AMainGameModeBase
{
	GENERATED_BODY()
	DECLARE_MULTICAST_DELEGATE(FOnDestroyFactoryEndedDelegate);

protected:
	UPROPERTY()
	TArray<ATankBuilder*> Builders;

public:
	FOnDestroyFactoryEndedDelegate OnDestroyFactoryEndedDelegate;

protected:
	virtual void Tick(float DeltaTime) override;

public:
	UFUNCTION(BlueprintCallable)
	void RegisterBuilder(ATankBuilder* Builder);

	UFUNCTION()
	void OnBuilderDie();
};
