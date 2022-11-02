// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/StaticMeshActor.h"
#include "GameFramework/Actor.h"
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
	void Tick(float DeltaSeconds) override;
	void BeginPlay() override;

private:
	FVector OriginalLocation;
	bool bMovingForward = true;
	FVector PlatformVelocity = FVector(100.f, 0.f, 0.f);

	float TimeElapsedSinceLastChange = 0.f;
	const float DurationToChangeDirection = 5.f;
};
