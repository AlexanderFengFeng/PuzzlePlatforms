// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

class UButton;
class UWidget;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UUserWidget
{
    GENERATED_BODY()

protected:
    virtual bool Initialize() override;

private:
    UPROPERTY(meta = (BindWidget))
    UButton* HostButton;
    UPROPERTY(meta = (BindWidget))
    UButton* JoinMenuButton;
    UPROPERTY(meta = (BindWidget))
    UButton* QuitGameButton;
    UPROPERTY(meta = (BindWidget))
    UButton* BackToMainMenuButton;
    UPROPERTY(meta = (BindWidget))
    UButton* JoinServerButton;

    UPROPERTY(meta = (BindWidget))
    class UWidgetSwitcher* MenuSwitcher;

    UPROPERTY(meta = (BindWidget))
    UWidget* JoinMenu;
    UPROPERTY(meta = (BindWidget))
    UWidget* MainMenu;

    UPROPERTY(meta = (BindWidget))
    class UEditableTextBox* IpAddressInput;

    UFUNCTION()
    void HostServer();
    UFUNCTION()
    void OpenJoinMenu();
    UFUNCTION()
    void QuitGame();
    UFUNCTION()
    void ReturnToMenu();
    UFUNCTION()
    void JoinServer();

    // To be filled in later to point to the specific menu interface.
    IMenuInterface* MenuInterface;

    APlayerController* PlayerController;
    UWorld* World;

public:
    void SetMenuInterface(IMenuInterface* MenuInterface);

    void Setup();
    virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
};
