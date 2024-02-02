// Fill out your copyright notice in the Description page of Project Settings.


#include "StatMenuWidgetController.h"
#include "GAS/AttributeInfo.h"
#include "GAS/RPGAttributeSet.h"
#include "RPGGameplayTags.h"

void UStatMenuWidgetController::BroadCastInitalValues()
{
	URPGAttributeSet* AS = CastChecked<URPGAttributeSet>(AttributeSet);
	check(AttributeInfo);

	//TEMP
	//FRPGAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(FRPGGameplayTags::Get().Attributes_MainStat_Intelligence);
	//Info.AttributeValue = AS->GetStrength();
	//AttributeInfoDelegate.Broadcast(Info);

	/*
		AttributeSet에 TagsToAttributes라는 Map을 이용해서 태그와 맵핑을 해놨다.
		이걸 통해 AttributeSet에 저장된 값들을 꺼내주고 있다.
	*/

	for (auto& Pair : AS->TagsToAttributes)
	{
		BroadcastAttributeInfo(Pair.Key, Pair.Value());
	}

	/*
		Broadcast되는 값들은, AttributeInfoDelegate에 등록을 해둔 각 WBP_TextValueRow에서 호출이 된다.
	*/

}

void UStatMenuWidgetController::BindCallbacksToDependencies()
{
	URPGAttributeSet* AS = CastChecked<URPGAttributeSet>(AttributeSet);

	for (auto& Pair : AS->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate
		(Pair.Value()).AddLambda([this, Pair, AS](const FOnAttributeChangeData& Data)
		{
			BroadcastAttributeInfo(Pair.Key, Pair.Value());
			//FRPGAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(Pair.Key);
			//Info.AttributeValue = Pair.Value().GetNumericValue(AS);
			//AttributeInfoDelegate.Broadcast(Info);
		});

	}
	
}

void UStatMenuWidgetController::BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute)
{
	FRPGAttributeInfo Info = AttributeInfo->FindAttributeInfoForTag(AttributeTag);
	Info.AttributeValue = Attribute.GetNumericValue(AttributeSet);
	AttributeInfoDelegate.Broadcast(Info);
}
