// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KFProjectile.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
UCLASS()
class KFSERVEROVERLAPS_API AKFProjectile : public AActor
{
	GENERATED_BODY()

public:
	AKFProjectile();

	UPROPERTY(EditAnywhere, Category="Editables")
	UStaticMeshComponent* SphereMesh;
	
protected:
	
	UPROPERTY()
	UProjectileMovementComponent* MovementComp;

};
