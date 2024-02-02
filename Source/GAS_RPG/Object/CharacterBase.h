// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "Interaction/CombatInterface.h"
#include "CharacterBase.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;
class UGameplayEffect;
class UGameplayAbility;

UCLASS()
class GAS_RPG_API ACharacterBase : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:

	ACharacterBase();

protected:
	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo();
	void				InitDefaultAttributes() const;
	void				ApplyEffectToSelf(TSubclassOf<UGameplayEffect> GameplayEffect, float Level) const;
	void				AddCharacterAbilities() const;

public:	

	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	virtual UAbilitySystemComponent*				GetAbilitySystemComponent() const override;
	UAttributeSet*														GetAttributeSet() const {return RPGAttributeSet;}

public:
	UPROPERTY(EditAnywhere, Category = "CharacterBase")
	TObjectPtr<USkeletalMeshComponent> Weapon;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<UAbilitySystemComponent> RPGAbilitySystemComponent;

	UPROPERTY(EditAnywhere, Category = "GAS")
	TObjectPtr<UAttributeSet> RPGAttributeSet;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attribute")
	TSubclassOf<UGameplayEffect> DefaultSubAttributes;

	UPROPERTY(EditAnywhere, Category = "Abilities")
	TArray<TSubclassOf<UGameplayAbility>>	StartupAbilities;

};
