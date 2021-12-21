// Fill out your copyright notice in the Description page of Project Settings.

using UnrealBuildTool;

public class DestructiveForce : ModuleRules
{
	public DestructiveForce(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicIncludePaths.AddRange(new string[]
		{
			"DestructiveForce",
			"DestructiveForce/Ui",
			"DestructiveForce/Ui/Slate",
			"DestructiveForce/Ui/Slate/Style",
		});

		PublicDependencyModuleNames.AddRange(new string[]
		{
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			"HeadMountedDisplay",
			"UMG"
		});

		PrivateDependencyModuleNames.AddRange(new string[]
		{
			"Slate",
			"SlateCore"
		});

		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}