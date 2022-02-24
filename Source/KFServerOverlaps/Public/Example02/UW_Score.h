// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UW_Score.generated.h"

class UTextBlock;

UCLASS()
class KFSERVEROVERLAPS_API UUW_Score : public UUserWidget
{
	GENERATED_BODY()

public:
	
	UFUNCTION()
	void UpdateScore(int iNewScore);
	
protected:
	
	virtual void NativeConstruct() override;
	
	UPROPERTY(BlueprintReadOnly, meta=(BindWidget))
	UTextBlock* Txt_ScoreCounter = nullptr;
	
};


