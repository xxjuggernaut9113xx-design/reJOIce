using UnrealBuildTool;
public class CockHeroRecovered : ModuleRules {
    public CockHeroRecovered(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "Json", "JsonUtilities", "MediaAssets", "UMG", "Slate", "SlateCore", "InputCore"});
        PrivateDependencyModuleNames.AddRange(new string[] {"HTTP", "WebSockets"});
        if (Target.Platform == UnrealTargetPlatform.Win64) PublicSystemLibraries.AddRange(new string[] {"Comdlg32.lib", "Shell32.lib", "Ole32.lib"});
        if (Target.bBuildEditor) PrivateDependencyModuleNames.AddRange(new string[] {"UnrealEd", "UMGEditor", "Kismet", "RHI", "BinkAudioDecoder", "TargetPlatform", "MovieScene", "MovieSceneTracks"});
    }
}
