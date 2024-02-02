// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "Interaction/MonsterInterface.h"
#include "GameplayTagContainer.h"
#include "RPGPlayerController.generated.h"

class UInputMappingContext;
class UInputAction;
class URPGInputConfig;
class URPGAbilitySystemComponent;
class USplineComponent;

UCLASS()
class GAS_RPG_API ARPGPlayerController : public APlayerController
{
	GENERATED_BODY()
public:

	ARPGPlayerController();

protected:
	
   virtual void BeginPlay() override;
   virtual void SetupInputComponent() override;
   virtual void Tick(float DeltaSeconds) override;
   virtual void PlayerTick(float DeltaTime) override;
   virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


   URPGAbilitySystemComponent* GetASC();

public:
	void CursorTrace();
	void AutoRun();


 private:
	
	//입력
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> PlayerInputContext;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	virtual void Move(const struct FInputActionValue& InputActionValue); 
	virtual void AbilityInputTagPressed(FGameplayTag InputTag);
	virtual void AbilityInputTagReleased(FGameplayTag InputTag);
	virtual void AbilityInputTagHeld(FGameplayTag InputTag);


private:
	TObjectPtr<IMonsterInterface> ThisActor;
	TObjectPtr<IMonsterInterface> LastActor;

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<URPGInputConfig> InputConfig;

	UPROPERTY()
	TObjectPtr<URPGAbilitySystemComponent> RPGASC;


	/****************
		Click Move
	****************/

	FVector CachedDestination = FVector::ZeroVector;
	float FollowTime = 0.f;
	float ShortPressThreshold = 0.5;
	bool bAutoRunning = false;
	bool bTargeting = false;

	UPROPERTY(EditDefaultsOnly)
	float AutoRunAccepttanceRadius = 50.f;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USplineComponent> Spline;



};
