// Fill out your copyright notice in the Description page of Project Settings.


#include "RPGAssetManager.h"
#include "RPGGameplayTags.h"

URPGAssetManager& URPGAssetManager::Get()
{
	check(GEngine);

	URPGAssetManager* Manager = Cast<URPGAssetManager>(GEngine->AssetManager);

	return * Manager;
}

void URPGAssetManager::StartInitialLoading()
{
	/*에셋매니저가 생성되면 FRPGGameplayTags의 Init을 통해 태그를 추가한다.*/
	FRPGGameplayTags::Init();
}
