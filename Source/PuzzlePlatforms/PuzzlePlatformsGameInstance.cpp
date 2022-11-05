// Fill out your copyright notice in the Description page of Project Settings.


#include "PuzzlePlatformsGameInstance.h"

UPuzzlePlatformsGameInstance::UPuzzlePlatformsGameInstance(const FObjectInitializer& ObjectInitializer)
{
    UE_LOG(LogTemp, Warning, TEXT("CONSTRUCTION"));
}

void UPuzzlePlatformsGameInstance::Init()
{
    Super::Init();
    UE_LOG(LogTemp, Warning, TEXT("INIT"));
}

