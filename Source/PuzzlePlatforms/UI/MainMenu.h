// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MainMenu.generated.h"

class UButton;

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
    UButton* JoinButton;

    UFUNCTION()
    void Host();
    UFUNCTION()
    void Join();

    // To be filled in later to point to the specific menu interface.
    IMenuInterface* MenuInterface;

public:
    void SetMenuInterface(IMenuInterface* MenuInterface);

    void Setup();
    virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;
};
