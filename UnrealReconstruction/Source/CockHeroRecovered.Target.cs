using UnrealBuildTool;
public class CockHeroRecoveredTarget : TargetRules {
    public CockHeroRecoveredTarget(TargetInfo Target) : base(Target) {
        Type = TargetType.Game;
        DefaultBuildSettings = BuildSettingsVersion.V4;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
        ExtraModuleNames.Add("CockHeroRecovered");
        bOverrideBuildEnvironment = true; // Project-local compatibility predicate; engine installation is unchanged.
        AdditionalCompilerArguments = "/FI\"" + System.IO.Path.Combine(ProjectFile.Directory.FullName, "Source", "CompilerCompatibility.h") + "\"";
    }
}
