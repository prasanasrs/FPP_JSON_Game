// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class FPP_Internship : ModuleRules
{
	public FPP_Internship(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "HTTP", "Json", "JsonUtilities" });
	}
}
