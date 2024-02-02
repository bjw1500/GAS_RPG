// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagsManager.h"

/**`
	Gameplay Tag를 관리하기 위한 구조체겸 싱글톤
 */

struct FRPGGameplayTags
{
public:
	static const FRPGGameplayTags& Get() {return GameplayTags;}
	static void	Init();

	FGameplayTag Attributes_MainStat_Strength;
	FGameplayTag Attributes_MainStat_Intelligence;
	FGameplayTag Attributes_MainStat_Resilience;
	FGameplayTag Attributes_MainStat_Vigor;

	FGameplayTag Attributes_SubStat_Armor;
	FGameplayTag Attributes_SubStat_ArmorPenetration;
	FGameplayTag Attributes_SubStat_BlockChance;
	FGameplayTag Attributes_SubStat_CriticalHitChance;
	FGameplayTag Attributes_SubStat_CriticalHitDamage;
	FGameplayTag Attributes_SubStat_CriticalHitResistance;
	FGameplayTag Attributes_SubStat_HealthRegeneration;
	FGameplayTag Attributes_SubStat_ManaRegeneration;
	FGameplayTag Attributes_SubStat_MaxMana;
	FGameplayTag Attributes_SubStat_MaxHealth;

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;
	FGameplayTag InputTag_1;
	FGameplayTag InputTag_2;
	FGameplayTag InputTag_3;
	FGameplayTag InputTag_4;

private:
	static FRPGGameplayTags GameplayTags;

 };
