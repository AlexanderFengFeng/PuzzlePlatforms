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
	virtual void BeginPlay() override;

	void AddActiveTrigger();
	void RemoveActiveTrigger();

protected:
	virtual void Tick(float DeltaSeconds) override;

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

    void SetUpPositionVectors();
	void Move(float DeltaSeconds);

	int CurrentTriggers = 0;
	UPROPERTY(EditAnywhere)
	int TargetTriggers = 0;
};

