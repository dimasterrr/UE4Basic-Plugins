#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

UCLASS()
class DESTRUCTIVEFORCE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly, Category = "Develope")
	FVector CurrentMousePosition;
	
private:
	void PerformMousePosition();

public:
	ATankPlayerController();
	virtual void Tick(float DeltaSeconds) override;
	
	FVector GetCurrentMousePosition() const;
};