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
