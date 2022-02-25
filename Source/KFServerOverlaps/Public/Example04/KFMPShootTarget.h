// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/TimelineComponent.h"
#include "GameFramework/Actor.h"
#include "KFMPShootTarget.generated.h"

class AKFMPVictim;
UCLASS()
class KFSERVEROVERLAPS_API AKFMPShootTarget : public AActor
{
	GENERATED_BODY()

public:
	AKFMPShootTarget();

	UFUNCTION(NetMulticast, Reliable)
	void PlayReverseAnim(bool _bForward);

protected:
	FTimeline CurveFTimeline;
	float fCurveFloatValue;
	float fTimelineValue;
	
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaSeconds) override;
	void LerpRotation(float _Alpha);
	
	UPROPERTY()
	USceneComponent* Scene;

	UPROPERTY()
	UCurveFloat* Anim;

	UPROPERTY(EditInstanceOnly, Category="Editables")
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(EditInstanceOnly, Category="Editables")
	UStaticMeshComponent* StaticMesh1;

	UPROPERTY(EditInstanceOnly, Category="Editables")
	USoundBase* SoundToUse;

	UPROPERTY(EditInstanceOnly, Category="Editables")
	AKFMPVictim* ConnectedVictim;

	UFUNCTION()
	void HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	UFUNCTION()
	void TimelineProgress(float Value);
};
