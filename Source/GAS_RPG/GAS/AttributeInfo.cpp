// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/AttributeInfo.h"

FRPGAttributeInfo UAttributeInfo::FindAttributeInfoForTag(const FGameplayTag AttributeTag, bool bLogNotFound)
{
	for (const FRPGAttributeInfo& Info : AttributeInformation)
	{
		if (Info.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Info;
		}

	}

	if (bLogNotFound)
	{
		UE_LOG(LogTemp, Error, TEXT("[%s]에서 [%s]를 찾지 못했습니다."), *GetNameSafe(this),*AttributeTag.ToString());
	}

	return FRPGAttributeInfo();
}
