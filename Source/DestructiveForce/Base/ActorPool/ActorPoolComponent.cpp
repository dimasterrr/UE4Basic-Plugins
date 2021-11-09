#include "ActorPoolComponent.h"
#include "ActorPoolable.h"

DEFINE_LOG_CATEGORY_STATIC(LogActorPool, Log, All)

UActorPoolComponent::UActorPoolComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UActorPoolComponent::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(GarbageCollectionHandle, this,
	                                       &UActorPoolComponent::OnGarbageCollectionActive,
	                                       GarbageCollectionInterval, true);
}

void UActorPoolComponent::OnGarbageCollectionActive()
{
	if (Pool.Num() == 0) return;

	const auto WorldTime = GetWorld()->GetTimeSeconds();
	for (auto Iterator = Pool.CreateIterator(); Iterator; ++Iterator)
	{
		if (WorldTime - Iterator->AdditionTime <= MaxObjectLifeTime) continue;
		
		UE_LOG(LogActorPool, Display, TEXT("Remove %s actor from pool."), *Iterator->Object->GetName());
		
		Iterator->Object->Destroy();
		Iterator.RemoveCurrent();
	}
}

AActorPoolable* UActorPoolComponent::GetOrCreate(const TSubclassOf<AActorPoolable> Class, const FTransform& Transform,
                                                 const FActorSpawnParameters& SpawnParameters)
{
	if (!Class)
	{
		UE_LOG(LogActorPool, Error, TEXT("Faild to spawn actor. Class is null!"));
		return nullptr;
	}

	AActorPoolable* TargetActor = nullptr;

	for (auto Iterator = Pool.CreateIterator(); Iterator; ++Iterator)
	{
		if (Iterator->Object->GetClass() != Class) continue;

		TargetActor = Iterator->Object;
		Iterator.RemoveCurrent();
	}

	if (!TargetActor)
	{
		TargetActor = Cast<AActorPoolable>(GetWorld()->SpawnActor(Class, &Transform, SpawnParameters));
		TargetActor->SetPool(this);
		
		UE_LOG(LogActorPool, Display, TEXT("Spawning new %s actor."), *TargetActor->GetName());
	}
	else
	{
		TargetActor->SetOwner(SpawnParameters.Owner);
		TargetActor->SetInstigator(SpawnParameters.Instigator);
		TargetActor->SetActorTransform(Transform);
		
		UE_LOG(LogActorPool, Display, TEXT("Get %s actor from pool."), *TargetActor->GetName());
	}

	TargetActor->Active();

	return TargetActor;
}

template <class T>
T* UActorPoolComponent::GetOrCreate(const TSubclassOf<AActorPoolable> Class, const FTransform& Transform,
                                    const FActorSpawnParameters& SpawnParameters)
{
	return Cast<T>(GetOrCreate(Class, Transform, SpawnParameters));
}

void UActorPoolComponent::Release(AActorPoolable* Value)
{
	FPullRecord NewRecord;
	NewRecord.Object = Value;
	NewRecord.AdditionTime = GetWorld()->GetTimeSeconds();

	Pool.Add(NewRecord);

	UE_LOG(LogActorPool, Display, TEXT("Actor %s return to pool."), *NewRecord.Object->GetName());
}
