// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example04/KFMPOverlap_Red.h"
#include "Components/BoxComponent.h"
#include "Example04/KF_Example04_Char.h"

AKFMPOverlap_Red::AKFMPOverlap_Red()
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
	bReplicates = false;
}

void AKFMPOverlap_Red::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this,&AKFMPOverlap_Red::OverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this,&AKFMPOverlap_Red::OverlapEnd);
}

void AKFMPOverlap_Red::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AKF_Example04_Char* TempChar = Cast<AKF_Example04_Char>(OtherActor);

	if(TempChar)
	{
		TempChar->Local_UpdateCanShoot(true);
	}
}

void AKFMPOverlap_Red::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	AKF_Example04_Char* TempChar = Cast<AKF_Example04_Char>(OtherActor);

	if(TempChar)
	{
		TempChar->Local_UpdateCanShoot(false);
	}
}
