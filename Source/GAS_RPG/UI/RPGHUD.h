// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "RPGHUD.generated.h"

/**
 * 
 */

 
 class URPGUserWidget;
 class UInGameWidgetController;
 class UStatMenuWidgetController;
 struct FWidgetControllerParams;

UCLASS()
class GAS_RPG_API ARPGHUD : public AHUD
{
	GENERATED_BODY()
public:

	UFUNCTION(BlueprintCallable)
	void Init(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS);

	UInGameWidgetController*			GetInGameWidgetController(const FWidgetControllerParams& WCParams);
	UStatMenuWidgetController*		GetStatMenuWidgetController(const FWidgetControllerParams& WCParams);

	UPROPERTY()
	TObjectPtr<URPGUserWidget> UI_Widget;

private:


	UPROPERTY(EditAnywhere)
	TSubclassOf<URPGUserWidget> UI_WidgetClass;

	/*InGameController*/
	UPROPERTY()
	TObjectPtr<UInGameWidgetController> InGameWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UInGameWidgetController> InGameWidgetControllerClass;


	/*StatMenuController*/
	UPROPERTY()
	TObjectPtr<UStatMenuWidgetController> StatMenuWidgetController;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UStatMenuWidgetController>StatMenuWidgetControllerClass;
};
