// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;
using System.IO;

public class panda : ModuleRules
{
	public panda(TargetInfo Target)
	{
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "Sockets", "Networking", "EasyKit" , "AIModule", "PerfCounters"});
        PublicDependencyModuleNames.AddRange(new string[] { "Json", "JsonUtilities", "UMG", "NeoFur" });
        PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore", "EasyKit", "PandaGameLoadingScreen" , "MoviePlayer" });
        LoadThirdParty(Target);

        PrivateIncludePaths.AddRange( 
            new string[] {
                "Panda/Private/Actor",
                "Panda/Private/AI",
                "Panda/Private/Character",
                "Panda/Private/Character/Monster",
                "Panda/Private/Character/Npc", 
                "Panda/Private/Character/Player",
                "Panda/Private/Component",
                "Panda/Private/Controller", 
                "Panda/Private/Gameplay",
                "Panda/Private/Manager",
                "Panda/Private/Networking",
                "Panda/Private/Animation",
                "Panda/Private/System",
                "Panda/Private/System/Quest",
                "Panda/Private/System/Quest/Condition",
                "Panda/Private/System/Quest/Task",
                "Panda/Private/System/Martialclub", 
                "Panda/Private/Scene",
                "Panda/Private/Server",
                "Panda/Private/Skill",
                "Panda/Private/Sound",
                "Panda/Private/Utils",
                "Panda/Private/Weapon",
                "Panda/Private/UI"
            }
        );

        PublicIncludePaths.AddRange(
            new string[] {
                "Panda/Public",
                "Panda/Classes/Actor",
                "Panda/Classes/AI",
                "Panda/Classes/Character",
                "Panda/Classes/Character/Monster",
                "Panda/Classes/Character/Npc",
                "Panda/Classes/Character/Player",
                "Panda/Classes/Character/SelectChar",
                "Panda/Classes/Common",
                "Panda/Classes/Component",
                "Panda/Classes/Controller",
                "Panda/Classes/DataManger",
                "Panda/Classes/Gameplay",
                "Panda/Classes/Gameplay/Procedure",
                "Panda/Classes/Gameplay/DataPool",
                "Panda/Classes/Manager",
                "Panda/Classes/Networking",
                "Panda/Classes/Animation",
                "Panda/Classes/System",
                "Panda/Classes/System/Quest",
                "Panda/Classes/System/Quest/Condition",
                "Panda/Classes/System/Quest/Task",
                "Panda/Classes/System/Martialclub",
                "Panda/Classes/Scene",
                "Panda/Classes/Server",
                "Panda/Classes/Skill",
                "Panda/Classes/Sound",
                "Panda/Classes/Utils",
                "Panda/Classes/Weapon",
                "Panda/Classes/UI"
            }
        );
    }

    string ThirdPartyPath
    {
        get { return Path.GetFullPath(Path.Combine(ModuleDirectory, "../../../pandanet/")); }
    }

    public bool LoadThirdParty(TargetInfo Target)
    {
        bool isLibrarySupported = true;
        string LibraryPath = Path.Combine(ThirdPartyPath, "bin");
        string LibraryName = "pandanet";
        if ((Target.Platform == UnrealTargetPlatform.Win64) || (Target.Platform == UnrealTargetPlatform.Win32))
        {
            PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, LibraryName + ".lib"));

            //PublicDelayLoadDLLs.Add(LibraryName+".dll");
            //RuntimeDependencies.Add(new RuntimeDependency(Path.Combine(LibraryPath, LibraryName+".dll")));
        }
        else if (Target.Platform == UnrealTargetPlatform.Mac)
        {
            PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, LibraryName + ".dylib"));
        }
        else if (Target.Platform == UnrealTargetPlatform.Linux)
        {
            PublicAdditionalLibraries.Add(Path.Combine(LibraryPath, "lib" + LibraryName + ".so"));
        }
        else
            isLibrarySupported = false;

        if (isLibrarySupported)
        {
            PublicIncludePaths.Add(ThirdPartyPath);
            PublicIncludePaths.Add(Path.Combine(ThirdPartyPath, "thirdparts", "include" ));
        }
        return isLibrarySupported;
    }
}
