#pragma once

#include "CoreMinimal.h"
#include "DestructiveForce/Base/PawnBase.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "TankPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class DESTRUCTIVEFORCE_API ATankPawn : public APawnBase
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadWrite, Category = "Components")
	UFloatingPawnMovement* FloatingPawnMovement;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "Movement|Speed")
	float TurretRotationInterpolationSpeed = .4f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category="Movement|Turret")
	FRotator CurrentTurretRotation;

protected:
	void PerformRotateTurret(float DeltaTime) const;

public:
	ATankPawn();

	virtual void Tick(float DeltaTime) override;

	void SetTurretRotation(const FRotator Value);
};
