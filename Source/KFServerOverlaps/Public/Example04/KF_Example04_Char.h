// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "KF_Example04_Char.generated.h"

class UCameraComponent;

UCLASS()
class KFSERVEROVERLAPS_API AKF_Example04_Char : public ACharacter
{
	GENERATED_BODY()

public:
	AKF_Example04_Char();
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(Client, Reliable)
	void Local_UpdateCanShoot(bool _bCanShoot);
	
protected:
	
	UPROPERTY(EditInstanceOnly, Category="Editables")
	USoundBase* SoundToUse;

	UPROPERTY(Replicated)
	bool bCanShoot;

	UPROPERTY()
	UCameraComponent* FirstPersonCam;

	UFUNCTION(Server, Reliable)
	void Server_SpawnProjectile(FVector _vSpawnLoc, FRotator _rSpawnRot);

	UFUNCTION(Server, Reliable)
	void Server_UpdateCanShoot(bool _bCanShoot);
	
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
