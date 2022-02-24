// © 2022 KITATUS and Friends LTD. All Rights Reserved.


#include "Example02/UW_Score.h"
#include "Components/TextBlock.h"

void UUW_Score::NativeConstruct()
{
	Super::NativeConstruct();
}

void UUW_Score::UpdateScore(int iNewScore)
{
	Txt_ScoreCounter->SetText(FText::AsNumber(iNewScore));
}

