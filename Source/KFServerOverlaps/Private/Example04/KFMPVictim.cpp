// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example04/KFMPVictim.h"
#include "Particles/ParticleSystemComponent.h"

AKFMPVictim::AKFMPVictim()
{
	PrimaryActorTick.bCanEverTick = false;
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	SetRootComponent(StaticMesh);
	
	Particle = CreateDefaultSubobject<UParticleSystemComponent>(FName("Particle"));
	Particle->SetupAttachment(StaticMesh);
	
	bReplicates = true;
	Particle->SetRelativeLocation(FVector(0.0f,0.0f,30.0f));
	Particle->SetAutoActivate(false);
	bDoOnce = false;
	
}

void AKFMPVictim::Ignite_PT2()
{
	MC_StopIgnite();
	bDoOnce = false;
}

void AKFMPVictim::MC_StopIgnite_Implementation()
{
	Particle->Deactivate();
}

void AKFMPVictim::MC_Ignite_Implementation()
{
	Particle->Activate(true);
}

void AKFMPVictim::Server_IgniteAnimation_Implementation()
{
	if(!bDoOnce)
	{
		bDoOnce = true;
		MC_Ignite();
		
		FTimerHandle TempHandle;
		GetWorld()->GetTimerManager().SetTimer(TempHandle, this, &AKFMPVictim::Ignite_PT2, 3.0f, false);
	}
}

