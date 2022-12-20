// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"
#include "Components/WidgetSwitcher.h"
#include "Components/EditableTextBox.h"
#include "Kismet/KismetSystemLibrary.h"


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
    return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* InMenuInterface)
{
    MenuInterface = InMenuInterface;
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

void UMainMenu::QuitGame()
{
    UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
}

void UMainMenu::ReturnToMenu()
{
    if (MenuSwitcher == nullptr || MainMenu == nullptr) return;
    MenuSwitcher->SetActiveWidget(MainMenu);
}

void UMainMenu::JoinServer()
{
    if (MenuInterface == nullptr || IpAddressInput == nullptr) return;
    FString IPAddress = IpAddressInput->GetText().ToString();
    MenuInterface->Join(IPAddress);
}


void UMainMenu::Setup()
{
    this->AddToViewport();
    if (PlayerController == nullptr) return;
    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = true;
}

void UMainMenu::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
    Super::OnLevelRemovedFromWorld(InLevel, InWorld);
    this->RemoveFromViewport();
    if (PlayerController == nullptr) return;
    FInputModeGameOnly InputModeData;
    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = false;
}
