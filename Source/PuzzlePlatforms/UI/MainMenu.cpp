// Fill out your copyright notice in the Description page of Project Settings.


#include "MainMenu.h"
#include "Components/Button.h"


bool UMainMenu::Initialize()
{
    bool Success = Super::Initialize();
    if (!Success || HostButton == nullptr || JoinButton == nullptr) {

        return false;
    }
    try
    {
        HostButton->OnClicked.AddDynamic(this, &UMainMenu::Host);
        JoinButton->OnClicked.AddDynamic(this, &UMainMenu::Join);
    }
    catch(...)
    {
        return false;
    }
    return true;
}

void UMainMenu::SetMenuInterface(IMenuInterface* InMenuInterface)
{
    MenuInterface = InMenuInterface;
}

void UMainMenu::Host()
{
    if (MenuInterface == nullptr) return;
    MenuInterface->Host();
}

void UMainMenu::Join()
{
    if (MenuInterface == nullptr) return;
    //MenuInterface->Join();
}

void UMainMenu::Setup()
{
    this->AddToViewport();
    UWorld* World = GetWorld();
    if (World == nullptr) return;

    APlayerController* PlayerController = World->GetFirstPlayerController();
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

    UWorld* World = GetWorld();
    if (World == nullptr) return;
    APlayerController* PlayerController = World->GetFirstPlayerController();
    if (PlayerController == nullptr) return;

    FInputModeGameOnly InputModeData;
    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = false;
}
