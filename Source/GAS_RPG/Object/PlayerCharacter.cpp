// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/InputComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/Controller.h"
#include "GameFramework/SpringArmComponent.h"
#include "GAS/RPGPlayerState.h"
#include "GAS/RPGAbilitySystemComponent.h"
#include "GAS/RPGAttributeSet.h"
#include "UI/RPGHUD.h"
#include "UI/InGameWidgetController.h"
#include "Controller/RPGPlayerController.h"

APlayerCharacter::APlayerCharacter()
{
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 400.f, 0.f);
	GetCharacterMovement()->bConstrainToPlane = true;
	GetCharacterMovement()->bSnapToPlaneAtStart = true;

	bUseControllerRotationPitch = false;
	bUseControllerRotationRoll = false;
	bUseControllerRotationYaw = false;


	/*
		카메라 위치나 회전 같은 상세 설정은 BP에서 해줄것.
	*/

	// Create a camera boom (pulls in towards the player if there is a collision)
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 400.0f; // The camera follows at this distance behind the character	
	SpringArm->bUsePawnControlRotation = true; // Rotate the arm based on the controller

	// Create a follow camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(SpringArm, USpringArmComponent::SocketName); // Attach the camera to the end of the boom and let the boom adjust to match the controller orientation
	FollowCamera->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
}

void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);


	//서버
	InitAbilityActorInfo();
	AddCharacterAbilities();


}

void APlayerCharacter::OnRep_PlayerState()
{

	//클라
	InitAbilityActorInfo();
}

int32 APlayerCharacter::GetLevel()
{
	ARPGPlayerState* RPGPlayerState = GetPlayerState<ARPGPlayerState>();

	return RPGPlayerState->GetPlayerLevel();
}

void APlayerCharacter::InitAbilityActorInfo()
{
	ARPGPlayerState* RPGPlayerState = GetPlayerState<ARPGPlayerState>();
	check(RPGPlayerState);
	RPGPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(RPGPlayerState, this);
	RPGAbilitySystemComponent = RPGPlayerState->GetAbilitySystemComponent();

	/*RPGAbilityComponent 세팅을 해준다*/
	Cast<URPGAbilitySystemComponent>(RPGAbilitySystemComponent)->AbilityActorInfoSet();

	RPGAttributeSet = RPGPlayerState->GetAttributeSet();

	ARPGPlayerController* RPGController = Cast<ARPGPlayerController> (GetController());
	if (RPGController != nullptr)
	{

		//HUD->Init을 통해서 InGameUI 생성
		ARPGHUD* HUD =Cast<ARPGHUD>(RPGController->GetHUD());
		if (HUD != nullptr)
		{
			HUD->Init(RPGController, RPGPlayerState, RPGAbilitySystemComponent, RPGAttributeSet);
		}

	}
	InitDefaultAttributes();
}
