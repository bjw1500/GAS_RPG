// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGGameplayTags.h"


FRPGGameplayTags FRPGGameplayTags::GameplayTags;

void FRPGGameplayTags::Init()
{
	GameplayTags.Attributes_MainStat_Strength = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.MainStat.Strength"), FString(TEXT("힘입니다. 공격력을 올려줍니다.")));
	GameplayTags.Attributes_MainStat_Intelligence = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.MainStat.Intelligence"), FString(TEXT("지능입니다. 마법공격과 마나를 올려줍니다.")));
	GameplayTags.Attributes_MainStat_Resilience = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.MainStat.Resilience"), FString(TEXT("회복력입니다.")));
	GameplayTags.Attributes_MainStat_Vigor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.MainStat.Vigor"), FString(TEXT("활력입니다. 체력을 올려줍니다.")));


	  GameplayTags.Attributes_SubStat_Armor = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.SubStat.Armor"), FString(TEXT("데미지를 감소해주는 방어력입니다.")));
	  GameplayTags.Attributes_SubStat_ArmorPenetration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.SubStat.ArmorPenetration"), FString(TEXT("방어력 관통입니다..")));
	  GameplayTags.Attributes_SubStat_BlockChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.SubStat.BlockChance"), FString(TEXT("방어 확률입니다.")));
	  GameplayTags.Attributes_SubStat_CriticalHitChance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.SubStat.CriticalHitChance"), FString(TEXT("크리티컬 확률입니다.")));
	  GameplayTags.Attributes_SubStat_CriticalHitDamage = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.SubStat.CriticalHitDamage"), FString(TEXT("크리티컬 데미지입니다.")));
	  GameplayTags.Attributes_SubStat_CriticalHitResistance = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.SubStat.CriticalHitResistance"), FString(TEXT("크리티컬 저항입니다.")));
	  GameplayTags.Attributes_SubStat_HealthRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.SubStat.HealthRegeneration"), FString(TEXT("체력 재생입니다.")));
	  GameplayTags.Attributes_SubStat_ManaRegeneration = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.SubStat.ManaRegeneration"), FString(TEXT("마력 재생입니다.")));
	  GameplayTags.Attributes_SubStat_MaxMana = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.SubStat.MaxMana"), FString(TEXT("최대 마나입니다.")));
	  GameplayTags.Attributes_SubStat_MaxHealth = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.SubStat.MaxHealth"), FString(TEXT("최대 체력입니다.")));

	  /*Input*/
	  GameplayTags.InputTag_LMB = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Input.RMB"), FString(TEXT("마우스 오른쪽 버튼")));
	  GameplayTags.InputTag_RMB =UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Input.LMB"), FString(TEXT("마우스 왼쪽 버튼")));
	  GameplayTags.InputTag_1 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Input.1"), FString(TEXT("1")));
	  GameplayTags.InputTag_2 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Input.2"), FString(TEXT("2")));
	  GameplayTags.InputTag_3= UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Input.3"), FString(TEXT("3")));
	  GameplayTags.InputTag_4 = UGameplayTagsManager::Get().AddNativeGameplayTag(FName("Attribute.Input.4"), FString(TEXT("4")));

}
