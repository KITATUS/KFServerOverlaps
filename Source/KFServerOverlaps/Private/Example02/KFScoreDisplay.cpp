// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example02/KFScoreDisplay.h"
#include "Components/TextRenderComponent.h"

AKFScoreDisplay::AKFScoreDisplay()
{
	PrimaryActorTick.bCanEverTick = false;
	Txt_Line01 = CreateDefaultSubobject<UTextRenderComponent>(FName("Txt_Line01"));
	Txt_Line01->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Txt_Line01->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	Txt_Line01->SetText(FText::FromString("CURRENT SCORE:"));
	SetRootComponent(Txt_Line01);

	Txt_Score = CreateDefaultSubobject<UTextRenderComponent>(FName("Txt_Score"));
	Txt_Score->SetHorizontalAlignment(EHorizTextAligment::EHTA_Center);
	Txt_Score->SetVerticalAlignment(EVerticalTextAligment::EVRTA_TextCenter);
	Txt_Score->SetText(FText::FromString("0"));
    Txt_Score->SetupAttachment(Txt_Line01);

	Txt_Score->SetRelativeLocation(FVector(0.0f,0.0f,-20.0f));
}

void AKFScoreDisplay::UpdateScore(int iNewScore)
{
	Txt_Score->SetText(FText::AsNumber(iNewScore));
}

