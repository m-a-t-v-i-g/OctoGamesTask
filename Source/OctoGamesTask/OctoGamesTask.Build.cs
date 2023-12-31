// Test task by matvig. All rights reserved.

using UnrealBuildTool;

public class OctoGamesTask : ModuleRules
{
	public OctoGamesTask(ReadOnlyTargetRules Target) : base(Target)
	{
		PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
	
		PublicDependencyModuleNames.AddRange(new string[] { "Core", "CoreUObject", "Engine", "InputCore", "EnhancedInput", "AIModule", "GameplayTasks" });
		PrivateDependencyModuleNames.AddRange(new string[] {  });
		
		PublicIncludePaths.AddRange(new string[] { "OctoGamesTask/Public/" });
		PrivateIncludePaths.AddRange(new string[] { "OctoGamesTask/Private/" });
	}
}
