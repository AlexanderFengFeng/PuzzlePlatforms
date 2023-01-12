// Fill out your copyright notice in the Description page of Project Settings.


#include "ServerRow.h"

#include "MainMenu.h"
#include "Components/Button.h"

/**
 * Sets up the UServerRow widget, settings its parent and index.
 *
 * @param RowParent A pointer to the UMainMenu* that this UServerRow will be used for.
 * @param RowIndex The index within the parent that this UServerRow represents.
 */
void UServerRow::SetUp(UMainMenu* RowParent, uint32 RowIndex)
{
    Parent = RowParent;
    Index = RowIndex;
    RowButton->OnClicked.AddDynamic(this, &UServerRow::OnRowButtonClicked);
}

/* Informs the parent that this UServerRow was selected. */
void UServerRow::OnRowButtonClicked()
{
    if (Parent != nullptr)
    {
        Parent->SelectIndex(Index);
    }
}
