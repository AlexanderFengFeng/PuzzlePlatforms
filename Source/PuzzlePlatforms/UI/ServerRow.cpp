// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"

#include "MainMenu.h"
#include "Components/Button.h"

void UServerRow::SetUp(UMainMenu* RowParent, uint32 RowIndex)
{
    Parent = RowParent;
    Index = RowIndex;
    RowButton->OnClicked.AddDynamic(this, &UServerRow::OnRowButtonClicked);
}

void UServerRow::OnRowButtonClicked()
{
    if (Parent != nullptr)
    {
        Parent->SelectIndex(Index);
    }
}
