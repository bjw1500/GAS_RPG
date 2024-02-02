// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "RPGGameplayTags.h"
#include "RPGInputConfig.generated.h"

USTRUCT(BlueprintType)
struct FRPGInputAction
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	const class UInputAction* InputAction = nullptr;

	UPROPERTY(EditDefaultsOnly)
	FGameplayTag InputTag = FGameplayTag();

};



UCLASS()
class GAS_RPG_API URPGInputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	
	const UInputAction* FindAbilityInputActionForTag(const FGameplayTag& InputTag) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FRPGInputAction> AbilityInputActions;
	
};
