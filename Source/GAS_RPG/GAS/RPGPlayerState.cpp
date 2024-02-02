// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGPlayerState.h"
#include "GAS/RPGAbilitySystemComponent.h"
#include "GAS/RPGAttributeSet.h"
#include "Net/UnrealNetwork.h"

ARPGPlayerState::ARPGPlayerState()
{
	NetUpdateFrequency = 100;

	RPGAbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>("RPGAbilitySystemComponent");
	RPGAbilitySystemComponent->SetIsReplicated(true);
	/*
		ReplicationMode :: Mixed

		액터의 오너는 반드시 컨트롤러야 한다.
		스테이트의 오너는 자동적으로 컨트롤러가 된다.

	*/
	RPGAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	RPGAttributeSet = CreateDefaultSubobject<URPGAttributeSet>("RPGAttributeSet");
}

void ARPGPlayerState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps)
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(ARPGPlayerState, Level);

}

UAbilitySystemComponent* ARPGPlayerState::GetAbilitySystemComponent() const
{
	return RPGAbilitySystemComponent;
}

void ARPGPlayerState::OnRep_Level(int32 OldLevel)
{
}
