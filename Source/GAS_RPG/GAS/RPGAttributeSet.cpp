// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "RPGGameplayTags.h"
#include "GameFramework/Character.h"




/*********************
	AttributeSet
**********************/


URPGAttributeSet::URPGAttributeSet()
{
	const FRPGGameplayTags GameplayTags = FRPGGameplayTags::Get();

	/*
		게임 태그와 Attribute를 맵핑.
	*/

	TagsToAttributes.Add(GameplayTags.Attributes_MainStat_Strength, GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_MainStat_Intelligence, GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_MainStat_Resilience, GetResilienceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_MainStat_Vigor, GetVigorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SubStat_Armor, GetArmorAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SubStat_ArmorPenetration, GetArmorPenetrationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SubStat_BlockChance, GetBlockChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SubStat_CriticalHitChance, GetCriticalHitChanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SubStat_CriticalHitDamage, GetCriticalHitDamageAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SubStat_CriticalHitResistance, GetCriticalHitResistanceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SubStat_HealthRegeneration, GetHealthRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SubStat_ManaRegeneration, GetManaRegenerationAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SubStat_MaxHealth, GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_SubStat_MaxMana, GetMaxManaAttribute);



}
/*
리플리케이트가 필요한 프로퍼티를 추가할 때는 반드시 이 함수도 추가하여야한다.
*/
void URPGAttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	//Replicate 되려는 값들을 등록해준다.

	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Strength, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Intelligence, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Resilience, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Vigor, COND_None, REPNOTIFY_Always);

	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, ArmorPenetration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, BlockChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, CriticalHitChance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, CriticalHitDamage, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, CriticalHitResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, HealthRegeneration, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, ManaRegeneration, COND_None, REPNOTIFY_Always);


	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(URPGAttributeSet, MaxMana, COND_None, REPNOTIFY_Always);


}

void URPGAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeBaseChange(Attribute, NewValue);
	/*
		속성의 현재 값에 대한 변경사항을 제일 먼저 알려오는 곳.
		NewValue 값을 바꾸어도 클램프 용도로 실제 값에는 영향을 못주니, 값 변경 전에 뭔가 할 게 있을 때만 사용하도록 하자.

		1. PreAttributeBaseChange(여기서 NewValue로 BaseValue에 영향을 줄 수 있음, 즉 클램핑)
		2. PreAttributeChange(여기서 NewValue로 CurrentValue에 영향을 줄 수 있음, 즉 클램핑)
		3. PostGameplayEffectsExecute(BaseValue가 변경되기 직전에 호출됨) .클램핑하기 좋은 지점)

		따라서 현재 Current 및 Base 값을 모두 고정하는 가장 좋은 방법은
		PreAttributeBaseChange() 및 PreAttributeChange() 메서드에 동일한 고정 논리를 추가하는 것 같습니다. 
		그리고 클램핑 없이 PostGameplayEffectExecute()를 그대로 두는 것이 더 좋습니다. 
	*/

	//if (Attribute == GetHealthAttribute())
	//{
	//	NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	//}
	//if (Attribute == GetManaAttribute())
	//{
	//	NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
	//}
}

void URPGAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Props.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();

	//Source
	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourceController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();

		if (Props.SourceController == nullptr && Props.SourceAvatarActor != nullptr)
		{
			if (APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourceController = Pawn->GetController();
			}
		}

		if (Props.SourceController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourceController->GetPawn());
		}
	}

	//Target
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);

		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);

	}

}


void URPGAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	/*
		GameplayEffect로 인해 데이터 변경 후에 호출되는 곳.
		그런데 이건 서버에서 실행이 되는가? 클라에서 실행이 되는가?
		
	*/

	FEffectProperties Props;
	SetEffectProperties(Data, Props);

	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
			SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}

	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetHealth(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));
	}
}

/*
	MainStat
*/


void URPGAttributeSet::OnRep_Strength(const FGameplayAttributeData& OldStrength) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Strength, OldStrength);
}

void URPGAttributeSet::OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Intelligence, OldIntelligence);
}

void URPGAttributeSet::OnRep_Resilience(const FGameplayAttributeData& OldResilience) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Resilience, OldResilience);
}

void URPGAttributeSet::OnRep_Vigor(const FGameplayAttributeData& OldVigor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Vigor, OldVigor);
}


/*
	SubStat
*/


void URPGAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Armor, OldArmor);
}

void URPGAttributeSet::OnRep_ArmorPenetration(const FGameplayAttributeData& OldArmorPenetration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ArmorPenetration, OldArmorPenetration);
}

void URPGAttributeSet::OnRep_BlockChance(const FGameplayAttributeData& OldBlockChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, BlockChance, OldBlockChance);
}

void URPGAttributeSet::OnRep_CriticalHitChance(const FGameplayAttributeData& OldCriticalHitChance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, CriticalHitChance, OldCriticalHitChance);
}

void URPGAttributeSet::OnRep_CriticalHitDamage(const FGameplayAttributeData& OldCriticalHitDamage) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, CriticalHitDamage, OldCriticalHitDamage);
}

void URPGAttributeSet::OnRep_CriticalHitResistance(const FGameplayAttributeData& OldCriticalHitResistance) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, CriticalHitResistance, OldCriticalHitResistance);
}

void URPGAttributeSet::OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealthRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, HealthRegeneration, OldHealthRegeneration);
}

void URPGAttributeSet::OnRep_ManaRegeneration(const FGameplayAttributeData& OldManaRegeneration) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, ManaRegeneration, OldManaRegeneration);
}

/*
	HP , MP
*/


void URPGAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth) const
{

	/*
		서버에서 변경이 되면, 변경 사항을 저장한다.
		이를 통해서 롤백이 필요할 때 값을 추적해서 되돌린다.
	*/
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Health, OldHealth);
}

void URPGAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxHealth, OldMaxHealth);
}

void URPGAttributeSet::OnRep_Mana(const FGameplayAttributeData& OldMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, Mana, OldMana);
}

void URPGAttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(URPGAttributeSet, MaxMana, OldMaxMana);
}