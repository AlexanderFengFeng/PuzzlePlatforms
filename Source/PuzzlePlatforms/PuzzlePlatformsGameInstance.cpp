// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"
#include "Engine/Engine.h"
#include "Interfaces/OnlineSessionInterface.h"
#include "UObject/ConstructorHelpers.h"
#include "OnlineSubsystem.h"
#include "OnlineSessionSettings.h"

#include "UI/InGameMenu.h"
#include "UI/MainMenu.h"
#include "UI/MenuWidget.h"

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
    if (IOnlineSubsystem* OnlineSubsystem = IOnlineSubsystem::Get())
    {
        SessionInterface = OnlineSubsystem->GetSessionInterface();
        if (SessionInterface.IsValid())
        {
            SessionInterface->OnCreateSessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnCreateSessionComplete);
            SessionInterface->OnDestroySessionCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnDestroySessionComplete);
            SessionInterface->OnFindSessionsCompleteDelegates.AddUObject(this, &UPuzzlePlatformsGameInstance::OnFindSessionsComplete);
            RefreshServerList();
        }
    }
}

void UPuzzlePlatformsGameInstance::LoadMainMenu()
{
    if (MainMenuClass == nullptr) return;

    MainMenu = CreateWidget<UMainMenu>(this, MainMenuClass);
    if (MainMenu == nullptr) return;

    MainMenu->Setup();
    MainMenu->SetMenuInterface(this);
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

void UPuzzlePlatformsGameInstance::CreateSession()
{
    if (SessionInterface.IsValid())
    {
        FOnlineSessionSettings SessionSettings;
        SessionSettings.bIsLANMatch = true;
        SessionSettings.NumPublicConnections = 2;
        SessionSettings.bShouldAdvertise = true;
        SessionInterface->CreateSession(0, SessionName, SessionSettings);
    }
}

/* Delegate called when session creation is complete. */
void UPuzzlePlatformsGameInstance::OnCreateSessionComplete(FName Session, bool Success)
{
    if (!Success)
    {
        UE_LOG(LogTemp, Warning, TEXT("Could not create session, %s"), *Session.ToString())
        return;
    }

    UEngine* Engine = GetEngine();
    if (Engine == nullptr) return;

    Engine->AddOnScreenDebugMessage(0, 3.f, FColor::Green, TEXT("Hosting..."));

    UWorld* World = GetWorld();
    if (World == nullptr) return;

    World->ServerTravel("/Game/ThirdPerson/Maps/ThirdPersonMap?listen");
}

/* Delegate called when session destruction is complete. */
void UPuzzlePlatformsGameInstance::OnDestroySessionComplete(FName Session, bool Success)
{
    if (!Success)
    {
        UE_LOG(LogTemp, Warning, TEXT("Could not destroy session, %s"), *Session.ToString())
        return;
    }
    // Creates a new session once a preexisting one has been cleaned up.
    CreateSession();
}

/* Delegate called when finding one or more sessions is complete. */
void UPuzzlePlatformsGameInstance::OnFindSessionsComplete(bool Success)
{
    if (!Success && SessionSearch.IsValid())
    {
        UE_LOG(LogTemp, Warning, TEXT("Could not find sessions"));
        return;
    }

    TArray<FString> ServerNames;
    for (auto& Result : SessionSearch->SearchResults)
    {
        ServerNames.Add(Result.GetSessionIdStr());
        UE_LOG(LogTemp, Warning, TEXT("Found session: %s"), *Result.GetSessionIdStr())
    }
    if (MainMenu != nullptr)
    {
        MainMenu->SetServerList(ServerNames);
    }
    UE_LOG(LogTemp, Warning, TEXT("Finished finding sessions"));
}

/* Public function to host a session. */
void UPuzzlePlatformsGameInstance::Host()
{
    if (SessionInterface.IsValid())
    {
        auto ExistingSession = SessionInterface->GetNamedSession(SessionName);
        if (ExistingSession == nullptr)
        {
            CreateSession();
        }
        else
        {
            SessionInterface->DestroySession(SessionName);
        }
    }
}

/* Public function to join a session. */
void UPuzzlePlatformsGameInstance::Join(const FString& Address)
{
    //UEngine* Engine = GetEngine();
    //if (Engine == nullptr) return;

    //Engine->AddOnScreenDebugMessage(0, 5.f, FColor::Green, FString::Printf(TEXT("Joining: %s"), *Address));

    //APlayerController* PlayerController = GetFirstLocalPlayerController();
    //if (PlayerController == nullptr) return;

    //PlayerController->ClientTravel(Address, ETravelType::TRAVEL_Absolute);
}

void UPuzzlePlatformsGameInstance::RefreshServerList()
{

    SessionSearch = MakeShareable(new FOnlineSessionSearch());
    if (SessionSearch.IsValid())
    {
        SessionSearch->bIsLanQuery = true;
        UE_LOG(LogTemp, Warning, TEXT("Finding sessions..."));
        if (MainMenu != nullptr)
        {
            MainMenu->ClearServerList();
        }
        SessionInterface->FindSessions(0, SessionSearch.ToSharedRef());
    }
}
