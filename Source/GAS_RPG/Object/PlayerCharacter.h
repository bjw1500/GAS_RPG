// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "PlayerCharacter.generated.h"


class URPGAttributeSet ;
class UAttributeSet;
class UAbilitySystemComponent;




UCLASS()
class GAS_RPG_API APlayerCharacter : public ACharacterBase
{
	GENERATED_BODY()
public:
	
	APlayerCharacter();
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;

	/*CombatInterface*/
	virtual int32 GetLevel() override;



private:
	virtual void InitAbilityActorInfo() override;


	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	class UCameraComponent* FollowCamera;
};
