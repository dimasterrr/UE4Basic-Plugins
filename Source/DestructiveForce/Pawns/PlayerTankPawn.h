// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TankPawn.h"
#include "PlayerTankPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class DESTRUCTIVEFORCE_API APlayerTankPawn : public ATankPawn
{
	GENERATED_BODY()

private:
	float ActiveForwardAxis = 0.f;
	float ActiveRightAxis = 0.f;
	float CurrentRightRate = 0.f;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationInterpolationSpeed = .4f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Effects")
	TSubclassOf<UCameraShakeBase> DamageCameraShakeTemplate;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Settings|Effects")
	float DamageCameraShakeRate;

private:
	void OnMoveForward(const float Value);
	void OnTurnRight(const float Value);

	void PerformMove(float DeltaTime);
	void PerformRotate(float DeltaTime);

public:
	APlayerTankPawn();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual bool TakeDamage(const FDamageData& Data) override;
	virtual void OnDieEvent() override;

	UFUNCTION(BlueprintImplementableEvent)
	void OnDieUi();
};
