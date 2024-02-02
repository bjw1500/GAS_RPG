// Fill out your copyright notice in the Description page of Project Settings.


#include "InGameWidgetController.h"
#include "GAS/RPGAttributeSet.h"
#include "GAS/RPGAbilitySystemComponent.h"

void UInGameWidgetController::BroadCastInitalValues()
{
	URPGAttributeSet* RPGAttributeSet = CastChecked<URPGAttributeSet>(AttributeSet);
	OnHealthChanged.Broadcast(RPGAttributeSet->GetHealth());
	OnMaxHealthChanged.Broadcast(RPGAttributeSet->GetMaxHealth());
	OnManaChanged.Broadcast(RPGAttributeSet->GetMana());
	OnMaxManaChanged.Broadcast(RPGAttributeSet->GetMaxMana());
}

void UInGameWidgetController::BindCallbacksToDependencies()
{
	URPGAttributeSet* RPGAttributeSet = CastChecked<URPGAttributeSet>(AttributeSet);

	/*
		GetGameplayAttributeValueChangeDelegate
		코드를 파고들어가면, 델리게이트가 찾아봤을 때 없을 경우 즉석에서 만들어서 넣어준다는걸 알 수 있다.
	*/

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGAttributeSet->GetHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnHealthChanged.Broadcast(Data.NewValue);
			});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGAttributeSet->GetMaxHealthAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnMaxHealthChanged.Broadcast(Data.NewValue);
			});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGAttributeSet->GetManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnManaChanged.Broadcast(Data.NewValue);
			});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(RPGAttributeSet->GetMaxManaAttribute())
		.AddLambda([this](const FOnAttributeChangeData& Data)
			{
				OnMaxManaChanged.Broadcast(Data.NewValue);
			});



	/*
		아이템 먹을 때마다 메시지 만들어내기
		 AbilityComponent의 델리게이트에 등록.
		 
		 OnGameplayEffectAppliedDelegateToSelf 델리게이트에 등록된 EffectAssetTags 델리게이트에 등록을 해준다.

	*/
	Cast<URPGAbilitySystemComponent>(AbilitySystemComponent)->EffectAssetTags.AddLambda(
		[this](const FGameplayTagContainer& TagContainer) {

			for (const FGameplayTag& Tag : TagContainer)
			{
				FGameplayTag MessageTag = FGameplayTag::RequestGameplayTag(FName("Message"));
				if(Tag.MatchesTag(MessageTag))
				{ 
					const FUIWidgetRow* Row = GetDataTableRowByTag<FUIWidgetRow>(MessageWidgetDataTable, Tag);
					if(Row == nullptr)
						return;

					/*델리게이트 브로드캐스트는 현재 블루프린트에서 만들어주고 있다*/
					MessageWidgetRowDelegate.Broadcast(*Row);
				}
			}
		}
	);

}

void UInGameWidgetController::HealthChanged(const FOnAttributeChangeData& Data) const
{
	OnHealthChanged.Broadcast(Data.NewValue);
}

void UInGameWidgetController::MaxHealthChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxHealthChanged.Broadcast(Data.NewValue);
}

void UInGameWidgetController::ManaChanged(const FOnAttributeChangeData& Data) const
{
	OnManaChanged.Broadcast(Data.NewValue);
}

void UInGameWidgetController::MaxManaChanged(const FOnAttributeChangeData& Data) const
{
	OnMaxManaChanged.Broadcast(Data.NewValue);
}

