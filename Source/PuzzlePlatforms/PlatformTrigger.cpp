// Fill out your copyright notice in the Description page of Project Settings.


#include "PlatformTrigger.h"
#include "Components/BoxComponent.h"
#include "MovingPlatform.h"


// Sets default values
APlatformTrigger::APlatformTrigger()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	TriggerVolume = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger Component"));
	if (TriggerVolume)
	{
	    SetRootComponent(TriggerVolume);
		TriggerVolume->OnComponentBeginOverlap.AddDynamic(this, &APlatformTrigger::BeginOverlap);
		TriggerVolume->OnComponentEndOverlap.AddDynamic(this, &APlatformTrigger::EndOverlap);
	}

}

// Called when the game starts or when spawned
void APlatformTrigger::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlatformTrigger::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlatformTrigger::BeginOverlap(UPrimitiveComponent* OverlappedComponent,
	                                AActor* OtherActor,
	                                UPrimitiveComponent* OtherComp,
									int32 OtherBodyIndex,
									bool bFromSweep,
									const FHitResult& SweepResult)
{
	for (AMovingPlatform* MovingPlatform : MovingPlatforms)
	{
		MovingPlatform->AddActiveTrigger();
	}
}

void APlatformTrigger::EndOverlap(UPrimitiveComponent* OverlappedComp,
								  AActor* OtherActor,
								  UPrimitiveComponent* OtherComp,
								  int32 OtherBodyIndex)
{
	for (AMovingPlatform* MovingPlatform : MovingPlatforms)
	{
		MovingPlatform->RemoveActiveTrigger();
	}
}
