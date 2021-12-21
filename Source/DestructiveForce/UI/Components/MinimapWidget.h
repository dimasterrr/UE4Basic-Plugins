#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "DestructiveForce/UI/Slate/SMinimap.h"
#include "MinimapWidgetStyle.h"
#include "MinimapWidget.generated.h"

UCLASS()
class DESTRUCTIVEFORCE_API UMinimapWidget : public UWidget
{
	GENERATED_BODY()

protected:
	TSharedPtr<SMinimap> Minimap;

public:
	UPROPERTY(EditAnywhere, Category = "Appearance", meta = (DisplayName = "Style"))
	FMinimapStyle WidgetStyle;
	
protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

public:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;

	virtual void SynchronizeProperties() override;

	UFUNCTION(BlueprintCallable)
	void UpdatePlayerPosition(const FVector2D& InPosition);
};
