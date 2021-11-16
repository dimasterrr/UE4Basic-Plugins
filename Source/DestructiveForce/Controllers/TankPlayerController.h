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
	ATankPawn* PossessedPawn = nullptr;

private:
	void PerformMousePosition(const float DeltaSeconds);

protected:
	virtual void OnPossess(APawn* InPawn) override;

public:
	ATankPlayerController();
	virtual void Tick(float DeltaSeconds) override;
};