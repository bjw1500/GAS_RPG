// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "RPGInputConfig.h"
#include "RPGInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API URPGInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	
	template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
	void BindAbilityActions(const URPGInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedRunc, HeldFuncType HeldFunc);
	
};

template<class UserClass, typename PressedFuncType, typename ReleasedFuncType, typename HeldFuncType>
inline void URPGInputComponent::BindAbilityActions(const URPGInputConfig* InputConfig, UserClass* Object, PressedFuncType PressedFunc, ReleasedFuncType ReleasedRunc, HeldFuncType HeldFunc)
{
	check(InputConfig);

	for (const FRPGInputAction& Action : InputConfig->AbilityInputActions)
	{
		if (Action.InputAction && Action.InputTag.IsValid())
		{
			if (PressedFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Started, Object, PressedFunc, Action.InputTag);
			}

			if (ReleasedRunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Completed, Object, ReleasedRunc, Action.InputTag);
			}

			if (HeldFunc)
			{
				BindAction(Action.InputAction, ETriggerEvent::Triggered, Object, HeldFunc, Action.InputTag);
			}

		}
	}
}
