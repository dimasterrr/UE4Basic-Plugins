#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ActorPoolComponent.generated.h"

class AActorPoolable;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DESTRUCTIVEFORCE_API UActorPoolComponent final : public UActorComponent
{
	GENERATED_BODY()

private:
	struct FPullRecord
	{
		AActorPoolable* Object = nullptr;
		float AdditionTime = 0.f;
	};

	TArray<FPullRecord> Pool;
	FTimerHandle GarbageCollectionHandle;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float GarbageCollectionInterval = 10.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings")
	float MaxObjectLifeTime = 10.f;

private:
	void OnGarbageCollectionActive();

protected:
	virtual void BeginPlay() override;

public:
	UActorPoolComponent();

	AActorPoolable* GetOrCreate(const TSubclassOf<AActorPoolable> Class,
	                            const FTransform& Transform,
	                            const FActorSpawnParameters& SpawnParameters = {});

	template <class T>
	T* GetOrCreate(const TSubclassOf<AActorPoolable> Class,
	               const FTransform& Transform,
	               const FActorSpawnParameters& SpawnParameters = {});

	void Release(AActorPoolable* Value);
};
