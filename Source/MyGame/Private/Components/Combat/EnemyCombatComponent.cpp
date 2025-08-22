// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/Combat/EnemyCombatComponent.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "MyGameplayTags.h"
#include "MyBlueprintFunctionLibrary.h"

#include "MyGameDebugHelper.h"

void UEnemyCombatComponent::OnHitTargetActor(AActor* HitActor)
{
	if (OverlappedActor.Contains(HitActor))
	{
		return;
	}

	OverlappedActor.AddUnique(HitActor);

	bool bIsValidBlock = false;

	const bool bIsPlayerBlocking = UMyBlueprintFunctionLibrary::NativeDoesActorHasTag(HitActor, MyGamePlayTags::Player_Status_Blocking);
	const bool bIsMyAttackUnableBlock = false;

	if (bIsPlayerBlocking && !bIsMyAttackUnableBlock)
	{
		//  judge can block ? set bIsValidBlock;
		bIsValidBlock = UMyBlueprintFunctionLibrary::IsValidBlock(GetOwningPawn(), HitActor);
	}

	FGameplayEventData EventData;
	EventData.Instigator = GetOwningPawn();
	EventData.Target = HitActor;
	
	if (bIsValidBlock)
	{
		//block success;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			HitActor,
			MyGamePlayTags::Player_Event_BlockSuccess,
			EventData
		);	
	}
	else
	{
		//block fail apply damage
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			GetOwningPawn(),
			MyGamePlayTags::Shared_Event_MeleeHit,
			EventData
		);
	}
}

