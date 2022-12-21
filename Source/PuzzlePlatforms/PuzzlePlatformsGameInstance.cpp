// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "UI/MainMenu.h"
#include "UI/InGameMenu.h"
#include "UI/MenuWidget.h"
#include "UObject/ConstructorHelpers.h"

// Occurs on beginning of game as well as in the editor after compilation.
UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
    ConstructorHelpers::FClassFinder<UMainMenu> MenuBPClass(TEXT("/Game/UI/WBP_MainMenu"));
    if (MenuBPClass.Class != nullptr)
    {
        MainMenuClass = MenuBPClass.Class;
    }
    ConstructorHelpers::FClassFinder<UInGameMenu> InGameMenuBPClass(TEXT("/Game/UI/WBP_InGameMenu"));
    if (InGameMenuBPClass.Class != nullptr)
    {
        InGameMenuClass = InGameMenuBPClass.Class;
    }
}

// Only occurs on beginning of game.
void UPuzzlePlatformsGameInstance::Init()
{
    Super::Init();
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
    if (MainMenuClass == nullptr) return;

    UMainMenu* Menu = CreateWidget<UMainMenu>(this, MainMenuClass);
    if (Menu == nullptr) return;

    Menu->Setup();
    Menu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::InGameLoadMenu()
{
    if (InGameMenuClass == nullptr) return;

    UMenuWidget* InGameMenu = CreateWidget<UMenuWidget>(this, InGameMenuClass);
    if (InGameMenu == nullptr) return;

    InGameMenu->Setup();
    InGameMenu->SetMenuInterface(this);
}

void UPuzzlePlatformsGameInstance::LoadMainMenuLevel()
{
    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (PlayerController != nullptr)
    {
        PlayerController->ClientTravel("/Game/Maps/MainMenu", ETravelType::TRAVEL_Absolute);
    }
}

void UPuzzlePlatformsGameInstance::Host()
{
    UEngine* Engine = GetEngine();
    if (Engine == nullptr) return;

    Engine->AddOnScreenDebugMessage(0, 3.f, FColor::Green, TEXT("Hosting..."));

    UWorld* World = GetWorld();
    if (World == nullptr) return;

    World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
    UEngine* Engine = GetEngine();
    if (Engine == nullptr) return;

    Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Joining: %s"), *Address));

    APlayerController* PlayerController = GetFirstLocalPlayerController();
    if (PlayerController == nullptr) return;

    PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}
