// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example02/KFProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

AKFProjectile::AKFProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("SphereMesh"));
	SetRootComponent(SphereMesh);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(FName("MovementComp"));
	MovementComp->InitialSpeed = 6000.0f;
	MovementComp->MaxSpeed = 6000.0f;
	MovementComp->bShouldBounce = true;
	MovementComp->Bounciness = 0.3f;
	
}
