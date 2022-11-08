// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"

// Occurs on beginning of game as well as in the editor after compilation.
UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("CONSTRUCTION"));
}

// Only occurs on beginning of game.
void UPuzzlePlatformsGameInstance::Init()
{
    Super::Init();
    UE_LOG(LogTemp, Warning, TEXT("INIT"));
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
