// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "KFScoreDisplay.generated.h"

class UTextRenderComponent;

UCLASS()
class KFSERVEROVERLAPS_API AKFScoreDisplay : public AActor
{
	GENERATED_BODY()

public:
	AKFScoreDisplay();

	UFUNCTION()
	void UpdateScore(int iNewScore);

protected:
	
	UPROPERTY()
	UTextRenderComponent* Txt_Score;
	
	UPROPERTY()
	UTextRenderComponent* Txt_Line01;
	
};
