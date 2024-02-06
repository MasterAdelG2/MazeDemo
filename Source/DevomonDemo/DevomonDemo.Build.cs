// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class DevomonDemo : ModuleRules
{
	public DevomonDemo(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput" });
	}
}
