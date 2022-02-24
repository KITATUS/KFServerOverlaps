// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KFShootVolume.generated.h"

class UBoxComponent;

UCLASS()
class KFSERVEROVERLAPS_API AKFShootVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	AKFShootVolume();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category="Changeables")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY()
	USceneComponent* DefaultSceneRoot;
	
	UPROPERTY()
	UBoxComponent* Box;

	UFUNCTION()
	void OverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void OverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
