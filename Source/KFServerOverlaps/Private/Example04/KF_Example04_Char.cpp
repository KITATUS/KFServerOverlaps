// © 2022 KITATUS and Friends LTD. All Rights Reserved.

#include "Example04/KF_Example04_Char.h"

#include "Camera/CameraComponent.h"
#include "Example04/KFMPProjectile.h"
#include "Kismet/GameplayStatics.h"
#include "Net/UnrealNetwork.h"

AKF_Example04_Char::AKF_Example04_Char()
{
	PrimaryActorTick.bCanEverTick = false;
	bCanShoot = false;
	fBaseTurnRate = 45.0f;
	fBaseLookUpRate = 45.0f;

	FirstPersonCam = CreateDefaultSubobject<UCameraComponent>(FName("FirstPersonCamera"));
	FirstPersonCam->SetupAttachment(GetRootComponent());
	FirstPersonCam->SetRelativeLocation(FVector(0.0f,0.0f,64.0f));
	FirstPersonCam->bUsePawnControlRotation = true;
	bReplicates = true;
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> TempFloat(TEXT("/Game/Example04/Meshes/TutorialTPP"));
	GetMesh()->SetSkeletalMesh(TempFloat.Object);
	GetMesh()->SetRelativeLocation(FVector(0.0f,0.0f,-90.0f));
	GetMesh()->SetRelativeRotation(FRotator(0.0f,-90.0f,0.0f));
	GetMesh()->SetOwnerNoSee(true);
}

void AKF_Example04_Char::Server_SpawnProjectile_Implementation(FVector _vSpawnLoc, FRotator _rSpawnRot)
{
	FActorSpawnParameters TempSpawnParam;
	TempSpawnParam.Owner = this;
	TempSpawnParam.Instigator = this;
	GetWorld()->SpawnActor<AKFMPProjectile>(AKFMPProjectile::StaticClass(),_vSpawnLoc, _rSpawnRot, TempSpawnParam);
}

void AKF_Example04_Char::Server_UpdateCanShoot_Implementation(bool _bCanShoot)
{
	bCanShoot = _bCanShoot;
}

void AKF_Example04_Char::BeginPlay()
{
	Super::BeginPlay();
}

void AKF_Example04_Char::TurnRate(float _fValue)
{
	AddControllerYawInput(_fValue * fBaseTurnRate * UGameplayStatics::GetWorldDeltaSeconds(this));
}

void AKF_Example04_Char::LookUpRate(float _fValue)
{
	AddControllerPitchInput(_fValue * fBaseLookUpRate * UGameplayStatics::GetWorldDeltaSeconds(this));
}

void AKF_Example04_Char::Turn(float _fValue)
{
	AddControllerYawInput(_fValue);
}

void AKF_Example04_Char::LookUp(float _fValue)
{
	AddControllerPitchInput(_fValue);
}

void AKF_Example04_Char::MoveForward(float _fValue)
{
	AddMovementInput(GetActorForwardVector(), _fValue, false);
}

void AKF_Example04_Char::MoveRight(float _fValue)
{
	AddMovementInput(GetActorRightVector(), _fValue, false);
}

void AKF_Example04_Char::Interact()
{
	if(bCanShoot)
	{
		Server_SpawnProjectile((FirstPersonCam->GetComponentLocation() + (FirstPersonCam->GetForwardVector() * 250.0f)), FirstPersonCam->GetForwardVector().ToOrientationRotator());
		UGameplayStatics::PlaySound2D(this, SoundToUse);
	}
}

void AKF_Example04_Char::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAxis("MoveForward", this, &AKF_Example04_Char::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AKF_Example04_Char::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AKF_Example04_Char::LookUp);
	PlayerInputComponent->BindAxis("LookUpRate", this, &AKF_Example04_Char::LookUpRate);
	PlayerInputComponent->BindAxis("Turn", this, &AKF_Example04_Char::Turn);
	PlayerInputComponent->BindAxis("TurnRate", this, &AKF_Example04_Char::TurnRate);
	PlayerInputComponent->BindAction("Interact", EInputEvent::IE_Pressed, this, &AKF_Example04_Char::Interact);
}

void AKF_Example04_Char::Local_UpdateCanShoot_Implementation(bool _bCanShoot)
{
	bCanShoot = _bCanShoot;
	Server_UpdateCanShoot(bCanShoot);
}

void AKF_Example04_Char::GetLifetimeReplicatedProps( TArray< FLifetimeProperty > & OutLifetimeProps ) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME( AKF_Example04_Char, bCanShoot);
}
