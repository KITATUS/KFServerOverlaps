// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KFMPOverlap_Green.generated.h"

class AKFMPShootTarget;
class UBoxComponent;

UCLASS()
class KFSERVEROVERLAPS_API AKFMPOverlap_Green : public AActor
{
	GENERATED_BODY()

public:
	AKFMPOverlap_Green();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category="Changeables")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditInstanceOnly, Category="Editables")
	AKFMPShootTarget* ConnectedTarget;

	UPROPERTY()
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY()
	UBoxComponent* Box;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION(Server, Reliable)
	void Server_CheckOverlap(AActor* _ActorRef, bool _bOverlapEnd);
};
