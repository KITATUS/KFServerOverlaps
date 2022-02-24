// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example02/KFShootTarget.h"

#include "Example02/KFProjectile.h"
#include "Example02/KFScoreDisplay.h"
#include "Example02/KF_Example02_Char.h"
#include "Example02/UW_Score.h"
#include "Kismet/GameplayStatics.h"

AKFShootTarget::AKFShootTarget()
{
	PrimaryActorTick.bCanEverTick = false;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	
}

void AKFShootTarget::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &AKFShootTarget::HitMesh);	
}

void AKFShootTarget::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AKFProjectile* TempBullet = Cast<AKFProjectile>(OtherActor);

	if(TempBullet)
	{
		UGameplayStatics::PlaySound2D(this, SoundToUse);
		iCurrentScore += 1;
		ScoreRef->UpdateScore(iCurrentScore);
		AKF_Example02_Char* TempChar = Cast<AKF_Example02_Char>(TempBullet->GetOwner());
		
		if(TempChar)
		{
			TempChar->ScoreWidget->UpdateScore(iCurrentScore);
		}
	}
}

