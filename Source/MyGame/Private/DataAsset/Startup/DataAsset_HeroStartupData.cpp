// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/Startup/DataAsset_HeroStartupData.h"
#include "AbilitySystem/Ability/MyGameplayAbility.h"
#include "AbilitySystem/Ability/HeroGameplayAbility.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"



void UDataAsset_HeroStartupData::GiveToAbilitySystemComponent(UMyAbilitySystemComponent* InASCToGive, int32 ApplyLevel)
{
    Super::GiveToAbilitySystemComponent(InASCToGive, ApplyLevel);
    
    for (const FHeroAbilitySet& AbilitySet : HeroStartupAbilitySet)
    {
        if (!AbilitySet.IsValid()) continue;

        FGameplayAbilitySpec AbilitySpec(AbilitySet.AbilityToGrant);

        AbilitySpec.SourceObject = InASCToGive->GetAvatarActor();
        AbilitySpec.Level = ApplyLevel;
        AbilitySpec.DynamicAbilityTags.AddTag(AbilitySet.InputTag);

        InASCToGive->GiveAbility(AbilitySpec);
    }
}
