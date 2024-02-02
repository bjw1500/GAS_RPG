// Fill out your copyright notice in the Description page of Project Settings.


#include "Monster.h"
#include "GAS_RPG.h"
#include "GAS/RPGAbilitySystemComponent.h"
#include "GAS/RPGAttributeSet.h"

AMonster::AMonster()
{
	//Collision 설정은 전부 Custom으로 변경
	GetMesh()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Block);

	///GAS
	RPGAbilitySystemComponent = CreateDefaultSubobject<URPGAbilitySystemComponent>("RPGAbilitySystemComponent");
	RPGAbilitySystemComponent->SetIsReplicated(true);
	RPGAbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	RPGAttributeSet = CreateDefaultSubobject<URPGAttributeSet>("RPGAttributeSet");
}

void AMonster::BeginPlay()
{
	Super::BeginPlay();
	InitAbilityActorInfo();

}

void AMonster::InitAbilityActorInfo()
{
	RPGAbilitySystemComponent->InitAbilityActorInfo(this, this);
}

void AMonster::HighlightActor()
{
	GetMesh()->SetRenderCustomDepth(true);
	GetMesh()->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	if (IsValid(Weapon) == true)
	{
		Weapon->SetRenderCustomDepth(true);
		Weapon->SetCustomDepthStencilValue(CUSTOM_DEPTH_RED);
	}

}

void AMonster::UnHighlightActor()
{
	GetMesh()->SetRenderCustomDepth(false);
	if (IsValid(Weapon) == true)
	{
		Weapon->SetRenderCustomDepth(false);
	}
}

int32 AMonster::GetLevel()
{
	return Level;
}
