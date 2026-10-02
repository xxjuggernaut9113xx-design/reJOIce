#include "Misc/AutomationTest.h"
#if WITH_DEV_AUTOMATION_TESTS && WITH_EDITOR
#include "RecoveredMediaPlayback.h"
#include "Materials/Material.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialExpressionTextureSampleParameter2D.h"
#include "MediaTexture.h"
#include "Dom/JsonObject.h"
#include "Serialization/JsonSerializer.h"
#include "Misc/FileHelper.h"
#include "Misc/Paths.h"

IMPLEMENT_SIMPLE_AUTOMATION_TEST(FRecoveredVideoMaterialTest,"CockHero.Recovery.VideoDisplayMaterial",EAutomationTestFlags::EditorContext|EAutomationTestFlags::EngineFilter)
bool FRecoveredVideoMaterialTest::RunTest(const FString& Parameters) {
    FString Text;TSharedPtr<FJsonObject> Evidence;
    if(!FFileHelper::LoadFileToString(Text,*(FPaths::ProjectDir()/TEXT("RecoveryEvidence/background-material-values.json"))) || !FJsonSerializer::Deserialize(TJsonReaderFactory<>::Create(Text),Evidence)) { AddError(TEXT("Missing material property evidence"));return false; }
    TestTrue(TEXT("Source material properties round-trip exactly"),Evidence->GetBoolField(TEXT("property_prefix_byte_identical_roundtrip")));
    TestFalse(TEXT("Stripped original graph is not claimed recovered"),Evidence->GetBoolField(TEXT("original_expression_graph_restored")));
    auto* Material=LoadObject<UMaterial>(nullptr,TEXT("/Game/Recovery/Resources/Video/Background_Video_Texture_Mat.Background_Video_Texture_Mat"));
    if(!TestNotNull(TEXT("Editable video display material"),Material)) return false;
    TestEqual(TEXT("Verified original UI material domain"),int32(Material->MaterialDomain),int32(Evidence->GetObjectField(TEXT("values"))->GetNumberField(TEXT("MaterialDomain"))));
    const auto& Expressions=Material->GetExpressionCollection().Expressions;
    TestEqual(TEXT("Editable replacement display graph"),Expressions.Num(),1);
    if(Expressions.Num()==1) {
        auto* Sample=Cast<UMaterialExpressionTextureSampleParameter2D>(Expressions[0]);
        if(TestNotNull(TEXT("Named media texture parameter"),Sample)) {
            TestEqual(TEXT("Display parameter"),Sample->ParameterName,FName(TEXT("BackgroundVideoTexture")));
            TestTrue(TEXT("External media sampler"),Sample->SamplerType==SAMPLERTYPE_External);
            TestTrue(TEXT("UI color output connected"),Material->GetEditorOnlyData()->EmissiveColor.Expression==Sample);
        }
    }
    auto* Playback=NewObject<URecoveredMediaPlayback>();
    TestNull(TEXT("No display material without a video texture"),Playback->GetVideoDisplayMaterial());
    Playback->VideoTexture=NewObject<UMediaTexture>(Playback);
    auto* First=Playback->GetVideoDisplayMaterial();
    if(!TestNotNull(TEXT("Runtime display instance"),First)) return false;
    UTexture* Bound=nullptr;
    TestTrue(TEXT("Runtime media parameter found"),First->GetTextureParameterValue(FMaterialParameterInfo(TEXT("BackgroundVideoTexture")),Bound));
    TestTrue(TEXT("Runtime texture bound"),Bound==Playback->VideoTexture);
    Playback->VideoTexture=NewObject<UMediaTexture>(Playback);
    TestTrue(TEXT("Display instance retained"),Playback->GetVideoDisplayMaterial()==First);
    First->GetTextureParameterValue(FMaterialParameterInfo(TEXT("BackgroundVideoTexture")),Bound);
    TestTrue(TEXT("Changed texture rebound"),Bound==Playback->VideoTexture);
    return true;
}
#endif
