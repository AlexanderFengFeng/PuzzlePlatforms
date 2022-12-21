// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "Kismet/KismetSystemLibrary.h"


void UMenuWidget::Setup()
{
    this->AddToViewport();
    if (PlayerController == nullptr) return;
    FInputModeUIOnly InputModeData;
    InputModeData.SetWidgetToFocus(this->TakeWidget());
    InputModeData.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = true;
}

void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
    Super::OnLevelRemovedFromWorld(InLevel, InWorld);
    Teardown();
}

void UMenuWidget::SetMenuInterface(IMenuInterface* InMenuInterface)
{
    MenuInterface = InMenuInterface;
}

void UMenuWidget::QuitGame()
{
    UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
}

void UMenuWidget::Teardown()
{
    this->RemoveFromViewport();
    if (PlayerController == nullptr) return;
    FInputModeGameOnly InputModeData;
    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = false;
}
