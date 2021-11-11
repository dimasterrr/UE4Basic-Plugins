#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "HealthComponent.generated.h"

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class DESTRUCTIVEFORCE_API UHealthComponent : public UActorComponent
{
	GENERATED_BODY()
	DECLARE_MULTICAST_DELEGATE_TwoParams(FOnHealthChangedDelegate, float /* Old health */, float /* New health */);
	DECLARE_MULTICAST_DELEGATE(FOnDieDelegate);

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings")
	float MaxHealth = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Settings")
	float Health = 100.f;

public:
	FOnHealthChangedDelegate OnHealthChangedDelegate;
	FOnDieDelegate OnDieDelegate;

public:
	UHealthComponent();

	UFUNCTION(BlueprintCallable)
	float GetHealth() const;

	UFUNCTION(BlueprintCallable)
	void SetHealth(const float NewHealth);
	
	UFUNCTION(BlueprintCallable)
	bool IsDie() const;
};
