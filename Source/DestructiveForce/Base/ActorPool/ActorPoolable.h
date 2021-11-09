#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ActorPoolable.generated.h"

class UActorPoolComponent;

UCLASS()
class DESTRUCTIVEFORCE_API AActorPoolable : public AActor
{
	GENERATED_BODY()

	friend class ObjectPoolComponent;

private:
	UActorPoolComponent* Pool = nullptr;;

protected:
	virtual void OnActivated();
	virtual void OnReleased();

public:
	UFUNCTION(BlueprintCallable)
	void SetPool(UActorPoolComponent* Value);

	UFUNCTION(BlueprintCallable)
	void Active();

	UFUNCTION(BlueprintCallable)
	void Release();
};
