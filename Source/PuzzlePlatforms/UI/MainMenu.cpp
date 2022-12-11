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

void UMainMenu::Host()
{
    UE_LOG(LogTemp, Warning, TEXT("HOSTING"));
}


void UMainMenu::Join()
{
    UE_LOG(LogTemp, Warning, TEXT("JOINING"));
}
