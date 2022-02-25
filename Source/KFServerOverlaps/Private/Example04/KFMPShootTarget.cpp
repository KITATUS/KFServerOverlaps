// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example04/KFMPShootTarget.h"

#include "Example04/KFMPProjectile.h"
#include "Example04/KFMPVictim.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"

AKFMPShootTarget::AKFMPShootTarget()
{
	PrimaryActorTick.bCanEverTick = true;
	Scene = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent(Scene);
	
	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh"));
	StaticMesh->SetupAttachment(Scene);
	
	StaticMesh1 = CreateDefaultSubobject<UStaticMeshComponent>(FName("StaticMesh1"));
	StaticMesh1->SetupAttachment(StaticMesh);

	static ConstructorHelpers::FObjectFinder<UCurveFloat> TempFloat(TEXT("/Game/Example04/Blueprints/FC_TargetAnim"));
	Anim = TempFloat.Object;
	
	bReplicates = true;
	StaticMesh->SetRelativeLocation(FVector::ZeroVector);
	StaticMesh->SetRelativeRotation(FRotator::ZeroRotator);
	StaticMesh1->SetRelativeLocation(FVector(0.0f,0.0f,-2.0f));
	StaticMesh1->SetRelativeRotation(FRotator(0.0f, 540.0f,540.0f));
	
}

void AKFMPShootTarget::PlayReverseAnim_Implementation(bool _bForward)
{
	if(_bForward)
	{
		CurveFTimeline.Play();
	}
	else
	{
		CurveFTimeline.Reverse();
	}
}


void AKFMPShootTarget::BeginPlay()
{
	Super::BeginPlay();
	StaticMesh->OnComponentHit.AddDynamic(this, &AKFMPShootTarget::HitMesh);
	if(Anim)
	{
		FOnTimelineFloat TempTimelineProgress;
		
		TempTimelineProgress.BindDynamic(this, &AKFMPShootTarget::TimelineProgress);
		
		CurveFTimeline.AddInterpFloat(Anim, TempTimelineProgress);
		CurveFTimeline.SetTimelineLength(0.60f);
		CurveFTimeline.SetLooping(false);
		CurveFTimeline.PlayFromStart();
	}
}

void AKFMPShootTarget::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	CurveFTimeline.TickTimeline(DeltaTime);
}

void AKFMPShootTarget::LerpRotation(float _Alpha)
{
	StaticMesh->SetRelativeRotation(UKismetMathLibrary::RLerp(FRotator(0.0f,0.0f,0.0f), FRotator(180.0f, 0.0f,0.0f), _Alpha, true));
}

void AKFMPShootTarget::HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit)
{
	AKFMPProjectile* TempBullet = Cast<AKFMPProjectile>(OtherActor);
	if(TempBullet)
	{
		UGameplayStatics::PlaySound2D(this, SoundToUse);
		ConnectedVictim->Server_IgniteAnimation();
	}
}

void AKFMPShootTarget::TimelineProgress(float Value)
{
	fTimelineValue = CurveFTimeline.GetPlaybackPosition();
	fCurveFloatValue = Anim->GetFloatValue(fTimelineValue);
	LerpRotation(fCurveFloatValue);
}

