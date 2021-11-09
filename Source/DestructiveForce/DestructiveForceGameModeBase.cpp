#include "DestructiveForceGameModeBase.h"
#include "DestructiveForce/Base/ActorPool/ActorPoolComponent.h"
#include "DestructiveForce/Projectiles/ProjectileBase.h"

ADestructiveForceGameModeBase::ADestructiveForceGameModeBase()
{
	ProjectilePool = CreateDefaultSubobject<UActorPoolComponent>("ProjectilePoolComponent");
}

void ADestructiveForceGameModeBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

UActorPoolComponent* ADestructiveForceGameModeBase::GetProjectilePool() const
{
	return ProjectilePool;
}
