// Fill out your copyright notice in the Description page of Project Settings.


#include "Input/RPGInputConfig.h"
#include "../Plugins/EnhancedInput/Source/EnhancedInput/Public/InputAction.h"

const UInputAction* URPGInputConfig::FindAbilityInputActionForTag(const FGameplayTag& InputTag) const
{
	for (const FRPGInputAction& Action : AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}

	}
	return nullptr;
}
