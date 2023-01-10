// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.h"
#include "MainMenu.generated.h"

class UButton;
class UWidget;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMainMenu : public UMenuWidget
{
    GENERATED_BODY()

public:
    UMainMenu(const FObjectInitializer& ObjectInitializer);

    void SetServerList(TArray<FString> ServerNames);
    void ClearServerList();

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
    UPanelWidget* ServerList;
    TSubclassOf<UUserWidget> ServerRowClass;


    UFUNCTION()
    void HostServer();
    UFUNCTION()
    void OpenJoinMenu();
    UFUNCTION()
    void ReturnToMenu();
    UFUNCTION()
    void JoinServer();
};
