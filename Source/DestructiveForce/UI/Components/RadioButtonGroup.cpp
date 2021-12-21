#include "RadioButtonGroup.h"
#include "DestructiveForce/UI/Slate/SRadioButtonGroup.h"

TSharedRef<SWidget> URadioButtonGroup::RebuildWidget()
{
	RadioButtonGroup = SNew(SRadioButtonGroup)
		.Style(&WidgetStyle)
		.OnRadioButtonChanged_UObject(this, &URadioButtonGroup::OnOnRadioButtonGroupChanged);

	return RadioButtonGroup.ToSharedRef();
}

void URadioButtonGroup::ReleaseSlateResources(bool bReleaseChildren)
{
	Super::ReleaseSlateResources(bReleaseChildren);

	RadioButtonGroup.Reset();
}

void URadioButtonGroup::OnOnRadioButtonGroupChanged(const int32 NewSelectedIndex)
{
	OnRadioButtonGroupChanged.Broadcast(NewSelectedIndex);
}
