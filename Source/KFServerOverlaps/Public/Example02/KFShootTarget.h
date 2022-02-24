// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KFShootTarget.generated.h"

class AKFScoreDisplay;

UCLASS()
class KFSERVEROVERLAPS_API AKFShootTarget : public AActor
{
	GENERATED_BODY()
	
public:	
	AKFShootTarget();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditInstanceOnly, Category="Editables")
	AKFScoreDisplay* ScoreRef;

	UPROPERTY(EditInstanceOnly, Category="Editables")
	UStaticMeshComponent* StaticMesh;

	UPROPERTY(EditInstanceOnly, Category="Editables")
	USoundBase* SoundToUse;

	UPROPERTY()
	int iCurrentScore;

	UFUNCTION()
	void HitMesh(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );
};
