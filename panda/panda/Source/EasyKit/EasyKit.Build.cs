// Copyright 1998-2014 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

// This module must be loaded "PreLoadingScreen" in the .uproject file, otherwise it will not hook in time!

public class EasyKit : ModuleRules
{
    public EasyKit(TargetInfo Target)
	{
        PrivateIncludePaths.AddRange(new string[] 
        { 
	        "EasyKit/Private",
            "EasyKit/Private/Factory",
	        "EasyKit/Private/Item",
            "EasyKit/Private/Player",
            "EasyKit/Private/Player/FSM",
	        "EasyKit/Private/NetWork",
            "EasyKit/Private/Actor",
            "EasyKit/Private/Map",
            "EasyKit/Private/UI",
            "EasyKit/Private/Physics/Collision"
        });

        PublicIncludePaths.AddRange(new string[] 
        { 
            "EasyKit/Public",
            "EasyKit/Public/Combat",
            "EasyKit/Public/Editor",
            "EasyKit/Classes/Item",
            "EasyKit/Classes/Player",
            "EasyKit/Classes/Player/FSM",
            "EasyKit/Classes/NetWork",
            "EasyKit/Classes/Actor",
            "EasyKit/Classes/Map",
            "EasyKit/Classes/UI",
            "EasyKit/Classes/Combo",
            "EasyKit/Classes/Physics/Collision",
            "EasyKit/Classes/Physics/Collision/Interface"
        });

        PrivateIncludePathModuleNames.AddRange(
             new string[] {
				"CrashTracker",
				"OnlineSubsystem", 
				"TargetPlatform",
				"DerivedDataCache",
				"ImageWrapper",
				"Advertising",
                "PandaGameLoadingScreen"
            }
           );

        PublicDependencyModuleNames.AddRange(
            new string[] {
                "UMG",
				"Core",
				"CoreUObject",
				"Engine",
                "OnlineSubsystem",
				"OnlineSubsystemUtils",
                "RenderCore",
            }
         );

        if (UEBuildConfiguration.bBuildEditor == true)
        {

            PrivateDependencyModuleNames.AddRange(
                new string[] {
                    "UnrealEd",
				    "MoviePlayer",
                    "UMG",
				    "Slate",
				    "SlateCore",
                    "AssetRegistry",
              
                }
            );

            //AddThirdPartyPrivateStaticDependencies(Target, "Net");
        }
        else
        {

            PrivateDependencyModuleNames.AddRange(
                new string[] {
				    "MoviePlayer",
                    "UMG",
				    "Slate",
				    "SlateCore",
                    "AssetRegistry",
            
                }
            );
            //AddThirdPartyPrivateStaticDependencies(Target, "Net");
        }

        if ((Target.Platform == UnrealTargetPlatform.Win32) || (Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Linux) || (Target.Platform == UnrealTargetPlatform.Mac))
        {
            if (UEBuildConfiguration.bCompileSteamOSS == true)
            {
                DynamicallyLoadedModuleNames.Add("OnlineSubsystemSteam");
            }

            DynamicallyLoadedModuleNames.Add("OnlineSubsystemNull");
        }

        //AddThirdPartyPrivateStaticDependencies(Target, "Net");
	}
}
