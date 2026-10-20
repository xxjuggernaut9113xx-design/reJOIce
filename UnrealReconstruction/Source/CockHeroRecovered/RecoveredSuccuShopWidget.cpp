#include "RecoveredSuccuShopWidget.h"
#include "RecoveredSuccuEconomy.h"
#include "Blueprint/WidgetTree.h"
#include "Components/VerticalBox.h"
#include "Components/HorizontalBox.h"
#include "Components/ScrollBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"

TSharedRef<SWidget> URecoveredSuccuShopRow::RebuildWidget() {
    if (!WidgetTree || WidgetTree->RootWidget) return Super::RebuildWidget();
    auto* Row=WidgetTree->ConstructWidget<UHorizontalBox>();
    WidgetTree->RootWidget=Row;
    Label=WidgetTree->ConstructWidget<UTextBlock>();
    Label->SetAutoWrapText(true);
    Row->AddChild(Label);
    BuyButton=WidgetTree->ConstructWidget<UButton>();
    auto* BuyText=WidgetTree->ConstructWidget<UTextBlock>();
    BuyText->SetText(FText::FromString(TEXT("Buy")));
    BuyButton->AddChild(BuyText);
    BuyButton->OnClicked.AddUniqueDynamic(this,&URecoveredSuccuShopRow::Buy);
    Row->AddChild(BuyButton);
    return Super::RebuildWidget();
}

void URecoveredSuccuShopRow::NativeConstruct() {
    Super::NativeConstruct();
    Refresh();
}

void URecoveredSuccuShopRow::Refresh() {
    if (!Label || !BuyButton || !Economy) return;
    const auto Catalog=URecoveredSuccuEconomy::GetCatalog();
    const auto* Entry=Catalog.FindByPredicate([this](const auto& Candidate) { return Candidate.Modifier==Modifier; });
    if (!Entry) return;
    Label->SetText(FText::FromString(FString::Printf(TEXT("%s — %d SuccuCoins\n%s%s"),*Entry->Title,Entry->Cost,*Entry->Description,Economy->HasModifier(Modifier) ? TEXT(" (Owned)") : TEXT(""))));
    BuyButton->SetIsEnabled(!Economy->HasModifier(Modifier) && Economy->SuccuCoins>=Entry->Cost);
}

void URecoveredSuccuShopRow::Buy() {
    if (Economy) Economy->Purchase(Modifier);
    Refresh();
}

TSharedRef<SWidget> URecoveredSuccuShopWidget::RebuildWidget() {
    if (!WidgetTree || WidgetTree->RootWidget) return Super::RebuildWidget();
    auto* Root=WidgetTree->ConstructWidget<UVerticalBox>();
    WidgetTree->RootWidget=Root;
    Balance=WidgetTree->ConstructWidget<UTextBlock>();
    Root->AddChild(Balance);
    auto* Scroll=WidgetTree->ConstructWidget<UScrollBox>();
    Root->AddChild(Scroll);
    for (const auto& Entry:URecoveredSuccuEconomy::GetCatalog()) {
        auto* Row=CreateWidget<URecoveredSuccuShopRow>(GetWorld(),URecoveredSuccuShopRow::StaticClass());
        if (!Row) continue;
        Row->Economy=Economy;
        Row->Modifier=Entry.Modifier;
        Scroll->AddChild(Row);
        Rows.Add(Row);
    }
    return Super::RebuildWidget();
}

void URecoveredSuccuShopWidget::NativeConstruct() {
    Super::NativeConstruct();
}

void URecoveredSuccuShopWidget::NativeTick(const FGeometry& Geometry,float DeltaTime) {
    Super::NativeTick(Geometry,DeltaTime);
    if (Economy && Balance) Balance->SetText(FText::FromString(FString::Printf(TEXT("SuccuCoins: %d"),Economy->SuccuCoins)));
    for (const auto& Row:Rows) if (Row) Row->Refresh();
}
