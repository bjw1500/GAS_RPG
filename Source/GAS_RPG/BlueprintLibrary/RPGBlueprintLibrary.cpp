// Fill out your copyright notice in the Description page of Project Settings.


#include "BlueprintLibrary/RPGBlueprintLibrary.h"
#include "UI/InGameWidgetController.h"
#include "UI/StatMenuWidgetController.h"
#include "Kismet/GameplayStatics.h"
#include "GAS/RPGPlayerState.h"
#include "UI/RPGHUD.h"

UInGameWidgetController* URPGBlueprintLibrary::GetInGameWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ARPGHUD* RPGHUD = Cast<ARPGHUD>(PC->GetHUD()))
		{
			ARPGPlayerState* PS = PC->GetPlayerState<ARPGPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return RPGHUD->GetInGameWidgetController(WidgetControllerParams);
		}

	}
	
	return nullptr;
}

UStatMenuWidgetController* URPGBlueprintLibrary::GetStatMenuWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PC = UGameplayStatics::GetPlayerController(WorldContextObject, 0))
	{
		if (ARPGHUD* RPGHUD = Cast<ARPGHUD>(PC->GetHUD()))
		{
			ARPGPlayerState* PS = PC->GetPlayerState<ARPGPlayerState>();
			UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
			UAttributeSet* AS = PS->GetAttributeSet();
			const FWidgetControllerParams WidgetControllerParams(PC, PS, ASC, AS);
			return RPGHUD->GetStatMenuWidgetController(WidgetControllerParams);
		}

	}

	return nullptr;
}
