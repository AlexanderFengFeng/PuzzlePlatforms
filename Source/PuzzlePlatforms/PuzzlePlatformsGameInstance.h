// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "Interfaces/OnlineSessionInterface.h"
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

	UFUNCTION(Exec, BlueprintCallable)
	virtual void LoadMainMenuLevel() override;
	UFUNCTION(Exec)
	virtual void Host() override;
	UFUNCTION(Exec)
	virtual void Join(const FString& Address) override;
	UFUNCTION(Exec)
	virtual void RefreshServerList() override;

private:
	virtual void Init() override;

	TSubclassOf<UUserWidget> MainMenuClass;
	TSubclassOf<UUserWidget> InGameMenuClass;

	class UMainMenu* MainMenu;

	const inline static FName SessionName = TEXT("Game Session");

	IOnlineSessionPtr SessionInterface;
	TSharedPtr<FOnlineSessionSearch> SessionSearch;

    void CreateSession();
	void OnCreateSessionComplete(FName Session, bool Success);
	void OnDestroySessionComplete(FName Session, bool Success);
	void OnFindSessionsComplete(bool Success);
};
