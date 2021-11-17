#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LevelPortal.generated.h"

class UBoxComponent;
UCLASS()
class DESTRUCTIVEFORCE_API ALevelPortal : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Components")
	UBoxComponent* BoxComponent;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Settings")
	TSoftObjectPtr<UWorld> Level;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Settings")
	bool IsPortalEnabled = false;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	                    UPrimitiveComponent* OtherComponent, int32 OtherBodyIndex, bool FromSweep,
	                    const FHitResult& SweepResult);

	void OnLoadLevel();

	UFUNCTION()
	void OnGameModeIsEnded();
	
	UFUNCTION(BlueprintImplementableEvent)
	void OnPortalEnableChanged();

public:
	ALevelPortal();

	void SetPortalEnable(const bool Enable);
};
