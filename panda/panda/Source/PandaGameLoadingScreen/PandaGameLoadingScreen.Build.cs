// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!

public class PandaGameLoadingScreen : ModuleRules
{
    public PandaGameLoadingScreen(TargetInfo Target)
	{
        PrivateIncludePaths.Add("../../Panda/Source/PlatformerGameLoadingScreen/Private");

        PrivateDependencyModuleNames.AddRange(
			new string[] {
				"Core",
				"CoreUObject",
				"MoviePlayer",
				"Slate",
				"SlateCore",
				"InputCore"
			}
		);
	}
} 
