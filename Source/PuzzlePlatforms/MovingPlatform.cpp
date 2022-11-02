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
    SetUpPositionVectors();
    if (HasAuthority())
    {
        SetReplicates(true);
        SetReplicateMovement(true);
    }
}

void AMovingPlatform::SetUpPositionVectors()
{
    // Set up direction vectors and values.
    OriginalLocation = GetActorLocation();
    GlobalTargetLocation = GetTransform().TransformPosition(TargetLocation);
    DirectionVector = (GlobalTargetLocation - OriginalLocation).GetSafeNormal();
    BoundingDistance = FVector::Dist(GlobalTargetLocation, OriginalLocation);
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
    FVector CurrentDestination = bMovingForward ? GlobalTargetLocation : OriginalLocation;
    if (FVector::Dist(CurrentOrigin, Location) >= BoundingDistance)
    {
        bMovingForward = !bMovingForward;
        Location = CurrentDestination;
    }
    SetActorLocation(Location);
}
