// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example04/KFMPOverlap_Green.h"
#include "Components/BoxComponent.h"
#include "Example04/KFMPShootTarget.h"
#include "Example04/KF_Example04_Char.h"

AKFMPOverlap_Green::AKFMPOverlap_Green()
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
	bReplicates = true;
}

void AKFMPOverlap_Green::BeginPlay()
{
	Super::BeginPlay();
	Box->OnComponentBeginOverlap.AddDynamic(this,&AKFMPOverlap_Green::OverlapBegin);
	Box->OnComponentEndOverlap.AddDynamic(this,&AKFMPOverlap_Green::OverlapEnd);
}

void AKFMPOverlap_Green::OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Server_CheckOverlap(OtherActor, false);
}

void AKFMPOverlap_Green::OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Server_CheckOverlap(OtherActor, true);
}

void AKFMPOverlap_Green::Server_CheckOverlap_Implementation(AActor* _ActorRef, bool _bOverlapEnd)
{
	AKF_Example04_Char* TempChar = Cast<AKF_Example04_Char>(_ActorRef);

	if(TempChar)
	{
		ConnectedTarget->PlayReverseAnim(_bOverlapEnd);
	}
}

