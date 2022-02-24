// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example02/KF_Example02_Char.h"
#include "Example02/UW_Score.h"
#include "Camera/CameraComponent.h"
#include "Example02/KFProjectile.h"
#include "Kismet/GameplayStatics.h"

AKF_Example02_Char::AKF_Example02_Char()
{
	PrimaryActorTick.bCanEverTick = false;
	bCanShoot = false;
	fBaseTurnRate = 45.0f;
	fBaseLookUpRate = 45.0f;

	FirstPersonCam = CreateDefaultSubobject<UCameraComponent>(FName("FirstPersonCamera"));
	FirstPersonCam->SetupAttachment(GetRootComponent());
	FirstPersonCam->SetRelativeLocation(FVector(0.0f,0.0f,64.0f));
	FirstPersonCam->bUsePawnControlRotation = true;
}

void AKF_Example02_Char::BeginPlay()
{
	Super::BeginPlay();
	ScoreWidget = CreateWidget<UUW_Score>(UGameplayStatics::GetPlayerController(this, 0), WidgetToUse);
	ScoreWidget->AddToViewport(0);
}

void AKF_Example02_Char::TurnRate(float _fValue)
{
	AddControllerYawInput(_fValue * fBaseTurnRate * UGameplayStatics::GetWorldDeltaSeconds(this));
}

void AKF_Example02_Char::LookUpRate(float _fValue)
{
	AddControllerPitchInput(_fValue * fBaseLookUpRate * UGameplayStatics::GetWorldDeltaSeconds(this));
}

void AKF_Example02_Char::Turn(float _fValue)
{
	AddControllerYawInput(_fValue);
}

void AKF_Example02_Char::LookUp(float _fValue)
{
	AddControllerPitchInput(_fValue);
}

void AKF_Example02_Char::MoveForward(float _fValue)
{
	AddMovementInput(GetActorForwardVector(), _fValue, false);
}

void AKF_Example02_Char::MoveRight(float _fValue)
{
	AddMovementInput(GetActorRightVector(), _fValue, false);
}

void AKF_Example02_Char::Interact()
{
	if(bCanShoot)
	{
		FActorSpawnParameters TempSpawnParam;
		TempSpawnParam.Owner = this;
		TempSpawnParam.Instigator = this;
		GetWorld()->SpawnActor<AKFProjectile>(AKFProjectile::StaticClass(),(FirstPersonCam->GetComponentLocation() + (FirstPersonCam->GetForwardVector() * 250.0f)), FirstPersonCam->GetForwardVector().ToOrientationRotator(), TempSpawnParam);
		UGameplayStatics::PlaySound2D(this, SoundToUse);
	}
}

void AKF_Example02_Char::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AKF_Example02_Char::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKF_Example02_Char::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AKF_Example02_Char::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AKF_Example02_Char::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &AKF_Example02_Char::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &AKF_Example02_Char::TurnRate);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &AKF_Example02_Char::Interact);
}

