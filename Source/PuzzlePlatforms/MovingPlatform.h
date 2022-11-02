// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "MovingPlatform.generated.h"

/**
 * 
 */
UCLASS()
class PUZZLEPLATFORMS_API AMovingPlatform : public AStaticMeshActor
{
	GENERATED_BODY()

public:
	AMovingPlatform();

protected:
	virtual void Tick(float DeltaSeconds) override;
	virtual void BeginPlay() override;

private:
	FVector OriginalLocation;
	bool bMovingForward = true;
	UPROPERTY(EditAnywhere)
	float PlatformVelocity = 100.f;
	UPROPERTY(EditInstanceOnly, Meta = (MakeEditWidget = true))
	FVector TargetLocation;
	FVector DirectionVector;
	FVector GlobalTargetLocation;
	float BoundingDistance;

	//float TimeElapsedSinceLastChange = 0.f;
	//const float DurationToChangeDirection = 5.f;

	void Move(float DeltaSeconds);
};

