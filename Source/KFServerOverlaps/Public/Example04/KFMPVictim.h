// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KFMPVictim.generated.h"

UCLASS()
class KFSERVEROVERLAPS_API AKFMPVictim : public AActor
{
	GENERATED_BODY()

public:
	AKFMPVictim();

	UFUNCTION(Server, Reliable)
	void Server_IgniteAnimation();

	void Ignite_PT2();

protected:

	UFUNCTION(NetMulticast, Reliable)
	void MC_Ignite();

	UFUNCTION(NetMulticast, Reliable)
	void MC_StopIgnite();
	
	UPROPERTY(EditInstanceOnly, Category="Editables")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditInstanceOnly, Category="Editables")
	UParticleSystemComponent* Particle;

	UPROPERTY()
	bool bDoOnce;
};
