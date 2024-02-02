// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "Interaction/MonsterInterface.h"
#include "Interaction/CombatInterface.h"
#include "Monster.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API AMonster : public ACharacterBase, public IMonsterInterface
{
	GENERATED_BODY()

public:
	AMonster();

	virtual void BeginPlay() override;
	virtual void InitAbilityActorInfo() override;

public:
	//Monster 인터페이스
	virtual void HighlightActor() override;
	virtual void UnHighlightActor() override;


	/*ICombatInterface*/
	virtual int32 GetLevel() override;


protected:

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Stat")
	int32 Level = 1;

};
