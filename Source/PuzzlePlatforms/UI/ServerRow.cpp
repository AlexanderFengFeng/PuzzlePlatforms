// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"

#include "MainMenu.h"
#include "Components/Button.h"

void UServerRow::SetUp(UMainMenu* Parent, uint32 Index)
{
    this->Parent = Parent;
    this->Index = Index;
    RowButton->OnClicked.AddDynamic(this, &UServerRow::OnRowButtonClicked);
}

void UServerRow::OnRowButtonClicked()
{
    Parent->SelectIndex(Index);
}
