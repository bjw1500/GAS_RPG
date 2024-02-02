// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAbilitySystemComponent.h"
#include "RPGGameplayAbility.h"

void URPGAbilitySystemComponent::AbilityActorInfoSet()
{
	/* 
	* OnGameplayEffectAppliedDelegateToSelf?
		GE가 자신에게 적용될 때마다 서버에서 호출됩니다. 
	*/
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &URPGAbilitySystemComponent::EffectApplied);
}

void URPGAbilitySystemComponent::EffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& EffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	//GEngine->AddOnScreenDebugMessage(1, 8.0f, FColor::Red, FString(TEXT("Effect Applied!")));
	
	
	//Gameplay Tag는 흥미롭게도 따로 전용 데이터 컨테이너가 존재한다.
	FGameplayTagContainer TagContainer;
	EffectSpec.GetAllAssetTags(TagContainer);

	/*적용된 효과의 태그들을 모아서 델리게이트와 연결된 함수들에게 브로드캐스트 해준다*/
	EffectAssetTags.Broadcast(TagContainer);

}

void URPGAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>> StartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> Class : StartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Class, 1);
		if (const URPGGameplayAbility* RPGAbility = Cast<URPGGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(RPGAbility->StartupInputTag);
			GiveAbility(AbilitySpec);

		}
	}

}

void URPGAbilitySystemComponent::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if(InputTag.IsValid() == false)
		return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputPressed(AbilitySpec);
			if (AbilitySpec.IsActive() == false)
			{
				TryActivateAbility(AbilitySpec.Handle);
			}
		}
	}

}


void URPGAbilitySystemComponent::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (InputTag.IsValid() == false)
		return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag))
		{
			AbilitySpecInputReleased(AbilitySpec);
		}
	}
}

void URPGAbilitySystemComponent::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (InputTag.IsValid() == false)
		return;
}
