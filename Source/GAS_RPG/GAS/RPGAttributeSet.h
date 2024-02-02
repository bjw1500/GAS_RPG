// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "RPGAttributeSet.generated.h"


 #define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
 	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)


	/*TEMP*/
DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature);
template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;



USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties(){}

	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourceController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
};

/**
 * 
 */
UCLASS()
class GAS_RPG_API URPGAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	URPGAttributeSet();

	virtual void GetLifetimeReplicatedProps( TArray<class FLifetimeProperty> & OutLifetimeProps ) const override;

	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData &Data) override;
	
	/*
		Main Stat
	*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Stat")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Strength);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Stat")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Intelligence);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Stat")
	FGameplayAttributeData Resilience;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Resilience);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Strength, Category = "Stat")
	FGameplayAttributeData Vigor;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Vigor);

	UFUNCTION()
	void OnRep_Strength(const FGameplayAttributeData& OldStrength) const;
	UFUNCTION()
	void OnRep_Intelligence(const FGameplayAttributeData& OldIntelligence) const;
	UFUNCTION()
	void OnRep_Resilience(const FGameplayAttributeData& OldResilience) const;
	UFUNCTION()
	void OnRep_Vigor(const FGameplayAttributeData& OldVigor) const;


	/*
		Sub Stat
	*/

	//방어력
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Armor, Category = "Sub Stat")
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Armor);
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldHealth) const;

	//방어 관통력
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ArmorPenetration, Category = "Sub Stat")
	FGameplayAttributeData ArmorPenetration;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ArmorPenetration);
	UFUNCTION()
	void OnRep_ArmorPenetration(const FGameplayAttributeData& OldHealth) const;

	//블럭 확률
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_BlockChance, Category = "Sub Stat")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, BlockChance);
	UFUNCTION()
	void OnRep_BlockChance(const FGameplayAttributeData& OldHealth) const;

	//크리터컬 확률
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitChance, Category = "Sub Stat")
	FGameplayAttributeData CriticalHitChance;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, CriticalHitChance);
	UFUNCTION()
	void OnRep_CriticalHitChance(const FGameplayAttributeData& OldHealth) const;

	//크리티컬 데미지
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitDamage, Category = "Sub Stat")
	FGameplayAttributeData CriticalHitDamage;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, CriticalHitDamage);
	UFUNCTION()
	void OnRep_CriticalHitDamage(const FGameplayAttributeData& OldHealth) const;

	//크리티컬 저항
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_CriticalHitResistance, Category = "Sub Stat")
	FGameplayAttributeData CriticalHitResistance;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, CriticalHitResistance);
	UFUNCTION()
	void OnRep_CriticalHitResistance(const FGameplayAttributeData& OldHealth) const;

	//체력 재생
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_HealthRegeneration, Category = "Sub Stat")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, HealthRegeneration);
	UFUNCTION()
	void OnRep_HealthRegeneration(const FGameplayAttributeData& OldHealth) const;

	//마나 재생
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_ManaRegeneration, Category = "Sub Stat")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, ManaRegeneration);
	UFUNCTION()
	void OnRep_ManaRegeneration(const FGameplayAttributeData& OldHealth) const;


	/*
		HP , MP
	*/

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Health, Category = "Stat")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Health);
		
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxHealth, Category = "Stat")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxHealth);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_Mana, Category = "Stat")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, Mana);

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing = OnRep_MaxMana, Category = "Stat")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(URPGAttributeSet, MaxMana);

	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldHealth) const;
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldMana) const;
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldMaxMana) const;


	/***********************/
	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;
	
private:

	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props) const;
};
