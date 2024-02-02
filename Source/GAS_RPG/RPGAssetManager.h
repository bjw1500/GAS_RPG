// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/AssetManager.h"
#include "RPGAssetManager.generated.h"

/**
 * 
 */
UCLASS()
class GAS_RPG_API URPGAssetManager : public UAssetManager
{
	GENERATED_BODY()

public:
	static URPGAssetManager& Get();

	/*엔진 실행 초기에 실행되는 함수*/
	virtual void StartInitialLoading() override;
	
};
