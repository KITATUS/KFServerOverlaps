// Fill out your copyright notice in the Description page of Project Settings.


#include "Example02/KFDunkTank.h"

// Sets default values
AKFDunkTank::AKFDunkTank()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AKFDunkTank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AKFDunkTank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

