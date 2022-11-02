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

    // Set up direction vectors and values.
    OriginalLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
    DirectionVector = (GlobalTargetLocation - OriginalLocation).GetSafeNormal();
    BoundingDistance = FVector::Dist(GlobalTargetLocation, OriginalLocation);

    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}

void AMovingPlatform::Tick(float DeltaSeconds)
{
    Super::Tick(DeltaSeconds);
    if (HasAuthority())
    {
        Move(DeltaSeconds);
    }
}

void AMovingPlatform::Move(float DeltaSeconds)
{
    FVector Location = GetActorLocation();
    int Direction = bMovingForward ? 1 : -1;
    Location += DirectionVector * DeltaSeconds * PlatformVelocity * Direction;

    FVector CurrentOrigin = bMovingForward ? OriginalLocation : GlobalTargetLocation;
    if (FVector::Dist(CurrentOrigin, GetActorLocation()) >= BoundingDistance)
    {
        bMovingForward = !bMovingForward;
    }
    SetActorLocation(Location);
}
