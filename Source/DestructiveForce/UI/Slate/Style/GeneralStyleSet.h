#pragma once

#include "CoreMinimal.h"

class DESTRUCTIVEFORCE_API FGeneralStyleSet
{
private:
	static TSharedPtr<ISlateStyle> StylePtr;

private:
	static TSharedPtr<ISlateStyle> FindStyle(const FString& ScopeToDirectory);

public:
	static void Initialize();
	static void Shutdown();

	static const ISlateStyle& Get();
};
