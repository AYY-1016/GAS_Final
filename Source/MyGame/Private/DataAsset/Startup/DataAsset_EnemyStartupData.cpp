// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/Startup/DataAsset_EnemyStartupData.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "AbilitySystem/Ability/EnemyGameplayAbility.h"

void UDataAsset_EnemyStartupData::GiveToAbilitySystemComponent(UMyAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
	Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);

	if (!EnemyCombatAbilities.IsEmpty())
	{
		for (const TSubclassOf<UEnemyGameplayAbility> AbilityClass : EnemyCombatAbilities)
		{
			if (!AbilityClass) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityClass);
			AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
			AbilitySpec.Level = ApplyLevel;

			InASCToGive->GiveAbility(AbilitySpec);
		}
	}
}
