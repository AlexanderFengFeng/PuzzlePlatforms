// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "UI/MenuInterface.h"
#include "PuzzlePlatformsGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UPuzzlePlatformsGameInstance : public UGameInstance, public IMenuInterface
{
	GENERATED_BODY()

public:
	UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer);

	UFUNCTION(Exec, BlueprintCallable)
	void InGameLoadMenu();
	UFUNCTION(Exec, BlueprintCallable)
	void LoadMainMenu();

	UFUNCTION(Exec)
	virtual void Host() override;
	UFUNCTION(Exec)
	virtual void Join(const FString& Address) override;

private:
	virtual void Init() override;

	TSubclassOf<UUserWidget> MainMenuClass;
	TSubclassOf<UUserWidget> InGameMenuClass;
};
