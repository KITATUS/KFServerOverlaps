// Fill out your copyright notice in the Description page of Project Settings.


#include "Example02/KFFiringZone.h"

// Sets default values
AKFFiringZone::AKFFiringZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKFFiringZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKFFiringZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

