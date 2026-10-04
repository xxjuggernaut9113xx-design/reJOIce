using UnrealBuildTool;
public class CockHeroRecoveredEditorTarget : TargetRules {
    public CockHeroRecoveredEditorTarget(TargetInfo Target) : base(Target) {
        Type = TargetType.Editor;
        DefaultBuildSettings = BuildSettingsVersion.V4;
        IncludeOrderVersion = EngineIncludeOrderVersion.Unreal5_3;
        ExtraModuleNames.Add("CockHeroRecovered");
        bOverrideBuildEnvironment = true; // Project-local compatibility predicate; engine installation is unchanged.
        string CompatHeader = System.IO.Path.Combine(ProjectFile.Directory.FullName, "Source", "CompilerCompatibility.h");
        // /FI is MSVC-only; clang treats it as an input file and breaks the link. Use -include on Linux.
        AdditionalCompilerArguments = (Target.Platform == UnrealTargetPlatform.Win64)
            ? "/FI\"" + CompatHeader + "\""
            : "-include \"" + CompatHeader + "\"";
    }
}
