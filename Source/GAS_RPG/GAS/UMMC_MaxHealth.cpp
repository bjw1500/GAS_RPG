// Fill out your copyright notice in the Description page of Project Settings.


#include "GAS/UMMC_MaxHealth.h"
#include "GAS/RPGAttributeSet.h"
#include "Interaction/CombatInterface.h"

UMMC_MaxHealth::UMMC_MaxHealth()
{
	VigorDef .AttributeToCapture = URPGAttributeSet::GetVigorAttribute();
	VigorDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;

	/*
		여기서 계산할 Attribute 속성값을 넣어주는 과정.
	*/
	VigorDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(VigorDef);

}

float UMMC_MaxHealth::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	//태그를 모은다.
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Vigor;

	/*Spec에 각종 값들이 존재할 것이고, 그 중에서 캡쳐해놨던 VigorDef를  통해 Vigor 값을 알아온다.*/
	GetCapturedAttributeMagnitude(VigorDef, Spec, EvaluateParameters, Vigor);
	Vigor = FMath::Max<float>(Vigor, 0.f);

	ICombatInterface* CombatInterface = Cast<ICombatInterface>(Spec.GetContext().GetSourceObject());
	const int32 PlayerLevel = CombatInterface->GetLevel();

	return 80.f + 2.5f * Vigor + 10.f * PlayerLevel;
}
