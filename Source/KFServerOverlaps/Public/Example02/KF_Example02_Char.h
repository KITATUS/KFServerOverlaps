// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KF_Example02_Char.generated.h"

class UCameraComponent;
class UUW_Score;

UCLASS()
class KFSERVEROVERLAPS_API AKF_Example02_Char : public ACharacter
{
	GENERATED_BODY()

public:
	AKF_Example02_Char();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY()
	bool bCanShoot;

	UPROPERTY(EditAnywhere, Category="Editables")
	TSubclassOf<UUW_Score> WidgetToUse;

	UPROPERTY()
	UUW_Score* ScoreWidget;

protected:
	
	UPROPERTY(EditInstanceOnly, Category="Editables")
	USoundBase* SoundToUse;

	UPROPERTY()
	UCameraComponent* FirstPersonCam;

	float fBaseTurnRate;
	float fBaseLookUpRate;

	virtual void BeginPlay() override;

	void TurnRate(float _fValue);
	void LookUpRate(float _fValue);
	void Turn(float _fValue);
	void LookUp(float _fValue);
	void MoveForward(float _fValue);
	void MoveRight(float _fValue);
	void Interact();
	
};
