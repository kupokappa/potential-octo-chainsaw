// Copyright Epic Games, Inc. All Rights Reserved.

using UnrealBuildTool;

public class SwitchInputPassthru : ModuleRules {
    public SwitchInputPassthru(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;

        PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore" });

        PrivateDependencyModuleNames.AddRange(new string[] { });

        //PublicDefinitions.Add("WIN32_LEAN_AND_MEAN");

        PublicDefinitions.AddRange(
            new string[]
            {
            "_WIN32_WINNT_WIN10_TH2",
            "_WIN32_WINNT_WIN10_RS1",
            "_WIN32_WINNT_WIN10_RS2",
            "_WIN32_WINNT_WIN10_RS3",
            "_WIN32_WINNT_WIN10_RS4",
            "_WIN32_WINNT_WIN10_RS5"
            }
            );

        // Uncomment if you are using Slate UI
        // PrivateDependencyModuleNames.AddRange(new string[] { "Slate", "SlateCore" });

        // Uncomment if you are using online features
        // PrivateDependencyModuleNames.Add("OnlineSubsystem");

        // To include OnlineSubsystemSteam, add it to the plugins section in your uproject file with the Enabled attribute set to true
    }
}
