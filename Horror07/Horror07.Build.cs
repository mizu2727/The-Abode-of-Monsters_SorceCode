// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Horror07 : ModuleRules
{
	public Horror07(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] 
		{ 
			"Core", 
			"CoreUObject", 
			"Engine", 
			"InputCore", 
			"EnhancedInput",
			"AIModule",
			"GameplayTasks",
			"NavigationSystem",
            "EnhancedInput",
			"Slate"
        });
	}
}
