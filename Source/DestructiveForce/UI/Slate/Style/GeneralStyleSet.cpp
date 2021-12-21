#include "GeneralStyleSet.h"

#include "Slate/SlateGameResources.h"
#include "Styling/SlateStyleRegistry.h"

TSharedPtr<ISlateStyle> FGeneralStyleSet::StylePtr = nullptr;

TSharedPtr<ISlateStyle> FGeneralStyleSet::FindStyle(const FString& ScopeToDirectory)
{
	return FSlateGameResources::New(FName("StyleSet"), ScopeToDirectory, ScopeToDirectory);;
}

void FGeneralStyleSet::Initialize()
{
	Shutdown();

	StylePtr = FindStyle("/Game/Blueprints/Widgets/Styles");
	FSlateStyleRegistry::RegisterSlateStyle(*StylePtr);
}

void FGeneralStyleSet::Shutdown()
{
	if (!StylePtr.IsValid()) return;

	FSlateStyleRegistry::UnRegisterSlateStyle(*StylePtr);
	StylePtr.Reset();
}

const ISlateStyle& FGeneralStyleSet::Get()
{
	if (!StylePtr.IsValid()) Initialize();

	return *StylePtr;
}
