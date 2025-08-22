// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartupDataBase.generated.h"

class UMyGameplayAbility;
class UMyAbilitySystemComponent;
class UGameplayEffect;
/**
 * 
 */
UCLASS()
class MYGAME_API UDataAsset_StartupDataBase : public UDataAsset
{
	GENERATED_BODY()


public:
	virtual void GiveToAbilitySystemComponent(UMyAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);



protected:
	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray< TSubclassOf<UMyGameplayAbility> > ActivateOnGivenAbilities;
	

	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray< TSubclassOf<UMyGameplayAbility> > ReactiveAbilities;

	UPROPERTY(EditDefaultsOnly, Category = "StartupData")
	TArray< TSubclassOf<UGameplayEffect> >StartupGameplayEffects;

	void GrantAbilities(TArray< TSubclassOf<UMyGameplayAbility> >& InAbilitiesToGive, UMyAbilitySystemComponent* InASCToGive, int32 ApplyLevel = 1);
};
