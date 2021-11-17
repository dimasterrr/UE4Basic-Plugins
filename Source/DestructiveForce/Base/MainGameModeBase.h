#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"

class AProjectileBase;
class UActorPoolComponent;

UCLASS()
class DESTRUCTIVEFORCE_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UActorPoolComponent* ProjectilePool = nullptr;

protected:
	virtual void Tick(float DeltaTime) override;

public:
	AMainGameModeBase();

	UFUNCTION(BlueprintPure)
	UActorPoolComponent* GetProjectilePool() const;
};
