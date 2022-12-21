// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameMenu.h"
#include "Components/Button.h"
#include "MainMenu.h"

bool UInGameMenu::Initialize()
{
    bool Success = Super::Initialize();
    World = GetWorld();
    if (World)
    {
        PlayerController = World->GetFirstPlayerController();
    }

    if (!Success || QuitGameButton == nullptr || BackToMainMenuButton == nullptr
        || BackToGameButton == nullptr) {
        return false;
    }
    QuitGameButton->OnClicked.AddDynamic(this, &UInGameMenu::QuitGame);
    //BackToMainMenuButton->OnClicked.AddDynamic(this, &UInGameMenu::ReturnToMenu);
    //BackToGameButton->OnClicked.AddDynamic(this, &UInGameMenu::JoinServer);
    return true;
}