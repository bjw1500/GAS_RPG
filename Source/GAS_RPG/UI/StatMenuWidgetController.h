// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPGWidgetController.h"
#include "GAS/AttributeInfo.h"
#include "StatMenuWidgetController.generated.h"

/**
	Stat Menu에서 일어나는 변화를 관리하기 위한 컨트롤러
 */
class UAttributeInfo;
struct FGameplayTag;
struct FGameplayAttribute;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FAttributeInfoSignature, const FRPGAttributeInfo&, Info);

UCLASS(BlueprintType, Blueprintable)
class GAS_RPG_API UStatMenuWidgetController : public URPGWidgetController
{
	GENERATED_BODY()
public:
	virtual void BroadCastInitalValues() override;
	virtual void BindCallbacksToDependencies() override;
	void				BroadcastAttributeInfo(const FGameplayTag& AttributeTag, const FGameplayAttribute& Attribute);
	
	UPROPERTY(BlueprintAssignable, Category = "GAS | Attributes")
	FAttributeInfoSignature AttributeInfoDelegate;

protected:
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UAttributeInfo> AttributeInfo;
};
