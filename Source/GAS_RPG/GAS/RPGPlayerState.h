// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"
#include "RPGPlayerState.generated.h"

/**
 * 
 */
 class UAbilitySystemComponent;
 class UAttributeSet;
UCLASS()
class GAS_RPG_API ARPGPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
public:
	ARPGPlayerState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty> & OutLifetimeProps);

		// IAbilitySystemInterface을(를) 통해 상속됨
	virtual UAbilitySystemComponent*				GetAbilitySystemComponent() const override;
	UAttributeSet*														GetAttributeSet() const {return RPGAttributeSet;}
	int32																			GetPlayerLevel() const {return Level;}

	UFUNCTION()
	void OnRep_Level(int32 OldLevel);

private:
	UPROPERTY(VisibleAnywhere, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> RPGAbilitySystemComponent;;

	UPROPERTY(VisibleAnywhere, Category = "GAS")
	TObjectPtr<UAttributeSet> RPGAttributeSet;

	UPROPERTY(VisibleAnywhere, ReplicatedUsing = OnRep_Level)
	int32	Level = 1;


};
