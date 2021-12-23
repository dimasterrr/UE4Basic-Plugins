#pragma once

#include "CoreMinimal.h"
#include "DestructiveForce/Pawns/PlayerTankPawn.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class DESTRUCTIVEFORCE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category="Develope")
	APlayerTankPawn* PossessedPawn = nullptr;

public:
	FSimpleMulticastDelegate OnLeftMouseButtonUp;

private:
	void PerformMousePosition(const float DeltaSeconds);


protected:
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;

	// Input events moved from pawn
	UFUNCTION()
	void OnMoveForward(float Value);
	
	UFUNCTION()
	void OnTurnRight(float Value);
	
	UFUNCTION()
	void OnFireStart();
	
	UFUNCTION()
	void OnFireStop();
	
	UFUNCTION()
	void OnFireSpecialStart();
	
	UFUNCTION()
	void OnFireSpecialStop();
	
	UFUNCTION()
	void OnReload();
	
	UFUNCTION()
	void OnSwitchWeapon();

public:
	ATankPlayerController();
	virtual void Tick(float DeltaSeconds) override;
};
