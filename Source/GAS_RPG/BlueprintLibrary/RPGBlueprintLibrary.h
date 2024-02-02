// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "RPGBlueprintLibrary.generated.h"

/**
 * 
 */

 class UInGameWidgetController;
 class UStatMenuWidgetController;

UCLASS()
class GAS_RPG_API URPGBlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintPure, Category = "RPGBlueprintLibrary | WidgetController")
	static UInGameWidgetController*			GetInGameWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "RPGBlueprintLibrary | WidgetController")
	static UStatMenuWidgetController*		GetStatMenuWidgetController(const UObject* WorldContextObject);
	
};
