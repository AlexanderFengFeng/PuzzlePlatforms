// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Blueprint/UserWidget.h"
#include "Engine/Engine.h"
#include "UObject/ConstructorHelpers.h"

// Occurs on beginning of game as well as in the editor after compilation.
UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
    ConstructorHelpers::FClassFinder<UUserWidget> MenuBPClass(TEXT("/Game/UI/WBP_MainMenu"));
    if (MenuBPClass.Class != nullptr)
    {
        MenuClass = MenuBPClass.Class;
    }
}

// Only occurs on beginning of game.
void UPuzzlePlatformsGameInstance::Init()
{
    Super::Init();
}

void UPuzzlePlatformsGameInstance::LoadMenu()
{
    if (MenuClass != nullptr)
    {
        UUserWidget* Menu = CreateWidget<UUserWidget>(this, MenuClass);
        if (Menu != nullptr)
        {
            Menu->AddToViewport();
        }
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
