// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/Startup/DataAsset_StartupDataBase.h"
#include "MyTypes/MyStructTypes.h"
#include "DataAsset_HeroStartupData.generated.h"



/**
 * 
 */
UCLASS()
class MYGAME_API UDataAsset_HeroStartupData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UMyAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;


private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData", meta = (TitleProperty = "InputTag"))
	TArray<FHeroAbilitySet> HeroStartupAbilitySet;
};
	