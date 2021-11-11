#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "GlobalPlayerState.generated.h"

UCLASS()
class DESTRUCTIVEFORCE_API AGlobalPlayerState : public APlayerState
{
	GENERATED_BODY()

private:
	UPROPERTY()
	int32 CurrentScores = 0;

public:
	UFUNCTION(BlueprintPure, Category = "Scores")
	int GetScores() const;

	UFUNCTION(BlueprintCallable, Category = "Scores")
	void AddScores(int Scores);
};