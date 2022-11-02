// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"

AMovingPlatform::AMovingPlatform()
{
    GetStaticMeshComponent()->SetMobility(EComponentMobility::Movable);
    PrimaryActorTick.bCanEverTick = true;
}

void AMovingPlatform::BeginPlay()
{
    Super::BeginPlay();
    OriginalLocation = GetActorLocation();
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    FVector Location = GetActorLocation();

    if (bMovingForward)
    {
        Location += PlatformVelocity * DeltaSeconds;
    }
    else
    {
        Location -= PlatformVelocity * DeltaSeconds;
    }

    TimeElapsedSinceLastChange += DeltaSeconds;
    if (TimeElapsedSinceLastChange >= DurationToChangeDirection)
    {
        TimeElapsedSinceLastChange = 0.f;
        bMovingForward = !bMovingForward;

    }
    SetActorLocation(Location);
}
