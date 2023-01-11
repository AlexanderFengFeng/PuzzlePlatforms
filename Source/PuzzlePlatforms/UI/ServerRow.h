// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ServerRow.generated.h"

class UMainMenu;
class UButton;

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API UServerRow : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta = (BindWidget))
	UButton* RowButton;

public:
	UPROPERTY(meta = (BindWidget))
	class UTextBlock* ServerName;

	void SetUp(UMainMenu* Parent, uint32 Index);

	UMainMenu* Parent;
	uint32 Index;

	UFUNCTION()
	void OnRowButtonClicked();
};
