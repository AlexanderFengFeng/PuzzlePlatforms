// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/WidgetSwitcher.h"
#include "UObject/ConstructorHelpers.h"

#include "ServerRow.h"

UMainMenu::UMainMenu(const FObjectInitializer& ObjectInitializer)
{
    ConstructorHelpers::FClassFinder<UServerRow> ServerRowBPClass(TEXT("/Game/UI/BP_ServerRow"));
    if (ServerRowBPClass.Class != nullptr)
    {
        ServerRowClass = ServerRowBPClass.Class;
    }
}

bool UMainMenu::Initialize()
{
    bool Success = Super::Initialize();
    World = GetWorld();
    if (World)
    {
        PlayerController = World->GetFirstPlayerController();
    }

    if (!Success || HostButton == nullptr || JoinMenu == nullptr || QuitGameButton == nullptr
        || BackToMainMenuButton == nullptr || JoinServerButton == nullptr) {

        return false;
    }
    HostButton->OnClicked.AddDynamic(this, &UMainMenu::HostServer);
    JoinMenuButton->OnClicked.AddDynamic(this, &UMainMenu::OpenJoinMenu);
    QuitGameButton->OnClicked.AddDynamic(this, &UMainMenu::QuitGame);
    BackToMainMenuButton->OnClicked.AddDynamic(this, &UMainMenu::ReturnToMenu);
    JoinServerButton->OnClicked.AddDynamic(this, &UMainMenu::JoinServer);
    if (LoadingServerList != nullptr)
    {
        LoadingServerList->SetText(FText::FromString(TEXT("LOADING SERVER LIST...")));
    }
    return true;
}


void UMainMenu::HostServer()
{
    if (MenuInterface == nullptr) return;
    MenuInterface->Host();
}

void UMainMenu::OpenJoinMenu()
{
    if (MenuSwitcher == nullptr || JoinMenu == nullptr) return;
    MenuSwitcher->SetActiveWidget(JoinMenu);
}

void UMainMenu::SetServerList(TArray<FString> ServerNames)
{
    if (World == nullptr) return;

    for (const FString& ServerName : ServerNames)
    {
        if (UServerRow* Row = CreateWidget<UServerRow>(World, ServerRowClass))
        {
            Row->ServerName->SetText(FText::FromString(ServerName));
            ServerList->AddChild(Row);
        }
    }
    if (LoadingServerList != nullptr)
    {
        if (ServerNames.IsEmpty())
        {
            LoadingServerList->SetText(FText::FromString(TEXT("NO SERVERS FOUND")));
        }
        else
        {
            LoadingServerList->SetText(FText::FromString(TEXT("SERVERS FOUND:")));
        }
    }
}

void UMainMenu::ClearServerList()
{
    ServerList->ClearChildren();
}

void UMainMenu::ReturnToMenu()
{
    if (MenuSwitcher == nullptr || MainMenu == nullptr) return;
    MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
    if (MenuInterface == nullptr) return;
    //FString IPAddress = IpAddressInput->GetText().ToString();
    //MenuInterface->Join(IPAddress);
    MenuInterface->Join("");
}
