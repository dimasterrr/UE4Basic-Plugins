#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "DestructiveForceGameModeBase.generated.h"

class AProjectileBase;
class UActorPoolComponent;

UCLASS()
class DESTRUCTIVEFORCE_API ADestructiveForceGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UActorPoolComponent* ProjectilePool = nullptr;

protected:
	virtual void Tick(float DeltaTime) override;

public:
	ADestructiveForceGameModeBase();

	UFUNCTION(BlueprintPure)
	UActorPoolComponent* GetProjectilePool() const;
};
