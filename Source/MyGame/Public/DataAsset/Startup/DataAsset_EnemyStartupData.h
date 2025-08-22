// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/Startup/DataAsset_StartupDataBase.h"
#include "DataAsset_EnemyStartupData.generated.h"

class UEnemyGameplayAbility;
/**
 * 
 */
UCLASS()
class MYGAME_API UDataAsset_EnemyStartupData : public UDataAsset_StartupDataBase
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UMyAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1) override;
	
private:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray< TSubclassOf < UEnemyGameplayAbility > > EnemyCombatAbilities;

};
