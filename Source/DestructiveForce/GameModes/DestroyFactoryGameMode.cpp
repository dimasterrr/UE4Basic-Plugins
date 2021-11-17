#include "DestroyFactoryGameMode.h"
#include "DestructiveForce/Environment/TankBuilder.h"
#include "DestructiveForce/Base/Health//HealthComponent.h"

void ADestroyFactoryGameMode::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void ADestroyFactoryGameMode::RegisterBuilder(ATankBuilder* Builder)
{
	if (!Builder) return;
	Builders.Add(Builder);
	Builder->GetHealthComponent()->OnDieDelegate.AddUObject(this, &ADestroyFactoryGameMode::OnBuilderDie);
}

void ADestroyFactoryGameMode::OnBuilderDie()
{
	bool IsAlive = false;
	for (const auto& Builder : Builders)
	{
		if (!Builder || Builder->GetHealthComponent()->IsDie()) continue;

		IsAlive = true;
		break;
	}

	if (!IsAlive) OnDestroyFactoryEndedDelegate.Broadcast();
}
