// Fill out your copyright notice in the Description page of Project Settings.


#include "MyTypes/MyStructTypes.h"
#include "AbilitySystem/Ability/HeroGameplayAbility.h"

bool FHeroAbilitySet::IsValid() const
{
	return InputTag.IsValid() && AbilityToGrant;
}
