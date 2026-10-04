using UnrealBuildTool;
public class CockHeroRecovered : ModuleRules {
    public CockHeroRecovered(ReadOnlyTargetRules Target) : base(Target) {
        PCHUsage = PCHUsageMode.UseExplicitOrSharedPCHs;
        PublicDependencyModuleNames.AddRange(new string[] {"Core", "CoreUObject", "Engine", "Json", "JsonUtilities", "MediaAssets", "UMG", "Slate", "SlateCore", "InputCore"});
        if (Target.bBuildEditor) PrivateDependencyModuleNames.AddRange(new string[] {"UnrealEd", "UMGEditor", "Kismet", "RHI", "BinkAudioDecoder", "TargetPlatform", "MovieScene", "MovieSceneTracks"});
    }
}
