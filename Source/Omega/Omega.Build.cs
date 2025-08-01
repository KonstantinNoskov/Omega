// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class Omega : ModuleRules
{
	public Omega(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
		PublicDefinitions.Add("NOMINMAX=0");
	
		PublicDependencyModuleNames.AddRange(new string[]
		{	
			// Core
			"Core",
			"CoreUObject",
			"Engine",
			"InputCore",
			
			// 2D
			"Paper2D",
			"Paper2DEditor",
			"PaperZD",
			"PaperZDEditor",
			
			// GAS
			"GameplayAbilities",
			"GameplayTags",
			"GameplayTasks",
			
			// UI
			"Slate",
			"SlateCore",
			"UMG",
			
			// AI
			"AIModule",
			
			// Input
			"EnhancedInput",
			
			// VFX
			"Niagara",
			
			// MVVM
			"ModelViewViewModel"
		});

		PrivateDependencyModuleNames.AddRange(new string[] { });

		// Uncomment if you are using Slate UI
		// PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });
		
		// Uncomment if you are using online features
		// PrivateDependencyModuleNames.Add("OnlineSubsystem");

		// To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
	}
}
