// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGHUD.h"
#include "InGameWidgetController.h"
#include "StatMenuWidgetController.h"
#include "RPGUserWidget.h"

void ARPGHUD::Init(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	checkf(UI_WidgetClass, TEXT("ARPG HUD ERROR! WidgetClass 확인"));
	checkf(InGameWidgetControllerClass, TEXT("ARPG HUD ERROR! InGameWidgetControllerClass 확인"));

	const FWidgetControllerParams WidgetControllerParam(PC, PS, ASC, AS);
	InGameWidgetController = GetInGameWidgetController(WidgetControllerParam);

	UI_Widget = CreateWidget<URPGUserWidget>(GetWorld(), UI_WidgetClass);
	UI_Widget->SetWidgetController(InGameWidgetController);
	InGameWidgetController->BroadCastInitalValues();
	UI_Widget->AddToViewport();
}

UInGameWidgetController* ARPGHUD::GetInGameWidgetController(const FWidgetControllerParams& WCParams)
{
	if (InGameWidgetController == nullptr)
	{
		InGameWidgetController = NewObject<UInGameWidgetController>(this, InGameWidgetControllerClass);
		InGameWidgetController->SetWidgetControllerParams(WCParams);
		InGameWidgetController->BindCallbacksToDependencies();
		return InGameWidgetController;
	}


	return InGameWidgetController;
}

UStatMenuWidgetController* ARPGHUD::GetStatMenuWidgetController(const FWidgetControllerParams& WCParams)
{
	if (StatMenuWidgetController == nullptr)
	{
		StatMenuWidgetController = NewObject<UStatMenuWidgetController>(this, StatMenuWidgetControllerClass);
		StatMenuWidgetController->SetWidgetControllerParams(WCParams);
		StatMenuWidgetController->BindCallbacksToDependencies();
		return StatMenuWidgetController;
	}

	return StatMenuWidgetController;
}
