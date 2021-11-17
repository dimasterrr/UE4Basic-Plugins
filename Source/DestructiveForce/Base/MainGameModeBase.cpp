#include "MainGameModeBase.h"
#include "DestructiveForce/Base/ActorPool/ActorPoolComponent.h"

AMainGameModeBase::AMainGameModeBase()
{
	ProjectilePool = CreateDefaultSubobject<UActorPoolComponent>("ProjectilePoolComponent");
}

void AMainGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UActorPoolComponent* AMainGameModeBase::GetProjectilePool() const
{
	return ProjectilePool;
}
