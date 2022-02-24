// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example02/KFShootVolume.h"
#include "Components/BoxComponent.h"
#include "Example02/KF_Example02_Char.h"

AKFShootVolume::AKFShootVolume()
{
	PrimaryActorTick.bCanEverTick = false;
	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(FName("DefaultSceneRoot"));
	SetRootComponent(DefaultSceneRoot);
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(DefaultSceneRoot);
	Box = CreateDefaultSubobject<UBoxComponent>(FName("Box"));
	Box->SetBoxExtent(FVector(74.0f, 125.0f, 100.0f));
	Box->SetupAttachment(StaticMesh);
	Box->SetRelativeLocation(FVector(0.0f,0.0f, 100.0f));
}

void AKFShootVolume::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this,&AKFShootVolume::OverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this,&AKFShootVolume::OverlapEnd);
}

void AKFShootVolume::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AKF_Example02_Char* TempChar = Cast<AKF_Example02_Char>(OtherActor);

	if(TempChar)
	{
		TempChar->bCanShoot = true;
	}
}

void AKFShootVolume::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AKF_Example02_Char* TempChar = Cast<AKF_Example02_Char>(OtherActor);

	if(TempChar)
	{
		TempChar->bCanShoot = false;
	}
}
