#pragma once

#include "CoreMinimal.h"
#include "Components/Widget.h"
#include "RadioButtonGroup.generated.h"

class SRadioButtonGroup;

UCLASS()
class DESTRUCTIVEFORCE_API URadioButtonGroup : public UWidget
{
	GENERATED_BODY()
	DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRadioButtonGroupChanged, int32, NewSelectedButton);

private:
	TSharedPtr<SRadioButtonGroup> RadioButtonGroup;

public:
	UPROPERTY(BlueprintAssignable)
	FOnRadioButtonGroupChanged OnRadioButtonGroupChanged;

private:
	void OnOnRadioButtonGroupChanged(const int32 NewSelectedIndex);

protected:
	virtual TSharedRef<SWidget> RebuildWidget() override;

public:
	virtual void ReleaseSlateResources(bool bReleaseChildren) override;
};
