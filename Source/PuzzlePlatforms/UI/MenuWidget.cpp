// Fill out your copyright notice in the Description page of Project Settings.


#include "MenuWidget.h"

#include "Kismet/KismetSystemLibrary.h"

/**
 * Sets up this UMenuWidget.
 *
 * - Adds this widget to the viewport.
 * - Sets the focus to this widget.
 * - Restricts player control to the mouse.
 */
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

/* Tears down the widget when its level is removed from the world. */
void UMenuWidget::OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld)
{
    Super::OnLevelRemovedFromWorld(InLevel, InWorld);
    Teardown();
}

/* Sets this widget's MenuInterface (to be used for generic menu actions). */
void UMenuWidget::SetMenuInterface(IMenuInterface* InMenuInterface)
{
    MenuInterface = InMenuInterface;
}

/* Quits the game. */
void UMenuWidget::QuitGame()
{
    UKismetSystemLibrary::QuitGame(this, PlayerController, EQuitPreference::Quit, false);
}

/* Removes the widget from the viewport and returns control from mouse-restricted. */
void UMenuWidget::Teardown()
{
    this->RemoveFromViewport();
    if (PlayerController == nullptr) return;
    FInputModeGameOnly InputModeData;
    PlayerController->SetInputMode(InputModeData);
    PlayerController->bShowMouseCursor = false;
}
