// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example04/KFMPProjectile.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Sets default values
AKFMPProjectile::AKFMPProjectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	SphereMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("SphereMesh"));
	SetRootComponent(SphereMesh);

	MovementComp = CreateDefaultSubobject<UProjectileMovementComponent>(FName("MovementComp"));
	MovementComp->InitialSpeed = 6000.0f;
	MovementComp->MaxSpeed = 6000.0f;
	MovementComp->bShouldBounce = true;
	MovementComp->Bounciness = 0.3f;
	bReplicates = true;

	const ConstructorHelpers::FObjectFinder<UStaticMesh> MeshObj(TEXT("/Game/Example01/Meshes/SM_Sphere"));
	if(MeshObj.Object)
	{
		SphereMesh->SetStaticMesh(MeshObj.Object);
	}	
}
