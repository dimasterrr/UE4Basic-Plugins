#include "HealthComponent.h"

UHealthComponent::UHealthComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

float UHealthComponent::GetHealth() const
{
	return Health;
}

void UHealthComponent::SetHealth(const float NewHealth)
{
	if (IsDie()) return;

	const auto OldHealth = Health;
	Health = FMath::Clamp(NewHealth, 0.f, MaxHealth);
	OnHealthChangedDelegate.Broadcast(OldHealth, NewHealth);

	if (IsDie()) OnDieDelegate.Broadcast();
}

bool UHealthComponent::IsDie() const
{
	return FMath::IsNearlyZero(Health);
}
