// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "TankPawn.generated.h"

class AWeaponBase;
class UBoxComponent;
class UArrowComponent;
class UStaticMeshComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class DESTRUCTIVEFORCE_API ATankPawn : public APawn
{
	GENERATED_BODY()

private:
	float ActiveForwardAxis = 0.f;
	float ActiveRightAxis = 0.f;

	float CurrentForwardRate = 0.f;
	float CurrentRightRate = 0.f;

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UBoxComponent* BoxCollision;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UStaticMeshComponent* BodyMesh;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UArrowComponent* WeaponSetupPoint;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UCameraComponent* Camera;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float MoveSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float RotationSpeed = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float InterpolationSpeed = .1f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float TurretRotationInterpolationSpeed = .4f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Turret|Weapon")
	TSubclassOf<AWeaponBase> DefaultWeaponClass;

	UPROPERTY(BlueprintReadOnly, Category = "Turret|Weapon")
	TArray<AWeaponBase*> EquipWeapons;

	UPROPERTY(BlueprintReadOnly, Category = "Turret|Weapon")
	int MaxEquipWeapons = 2;

	UPROPERTY(BlueprintReadOnly, Category = "Turret|Weapon")
	int EquipWeaponIndex = INDEX_NONE;

private:
	void OnMoveForward(const float Value);
	void OnTurnRight(const float Value);

	void OnFireStart();
	void OnFireStop();

	void OnFireSpecialStart();
	void OnFireSpecialStop();

	void OnReload();
	void OnSwitchWeapon();

	void PerformMove(float DeltaTime);
	void PerformRotate(float DeltaTime);
	void PerformRotateTurret(float DeltaTime) const;

	AWeaponBase* GetActiveWeapon() const;

protected:
	virtual void BeginPlay() override;

public:
	ATankPawn();

	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable)
	void SetWeapon(TSubclassOf<AWeaponBase> WeaponClass);

	UFUNCTION(BlueprintCallable)
	void AddAmmoToWeapon(const TSubclassOf<AWeaponBase>& WeaponClass, int Value);
};
