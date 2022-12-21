// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuInterface.h"
#include "MenuWidget.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
    UFUNCTION()
    void QuitGame();
    UFUNCTION()
    void Teardown();

    IMenuInterface* MenuInterface;

    APlayerController* PlayerController;
    UWorld* World;

public:
    void Setup();
    virtual void OnLevelRemovedFromWorld(ULevel* InLevel, UWorld* InWorld) override;

    void SetMenuInterface(IMenuInterface* MenuInterface);
};
