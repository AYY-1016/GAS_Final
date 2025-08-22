// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/MyAbilitySystemComponent.h"
#include "Interface/PawnCombatInterface.h"
#include "GenericTeamAgentInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "MyGameplayTags.h"

#include "MyGameDebugHelper.h"
UMyAbilitySystemComponent* UMyBlueprintFunctionLibrary::NativeGetMyASCFromActor(AActor* InActor)
{
	check(InActor);
	return CastChecked<UMyAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor));

}

void UMyBlueprintFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, FGameplayTag TagToAdd)
{
	UMyAbilitySystemComponent* ASC = NativeGetMyASCFromActor(InActor);

	if (!ASC->HasMatchingGameplayTag(TagToAdd))
	{
		ASC->AddLooseGameplayTag(TagToAdd);
	}
}

void UMyBlueprintFunctionLibrary::RemoveGameplayTagFromActorIfFound(AActor* InActor, FGameplayTag TagToRemove)
{
	UMyAbilitySystemComponent* ASC = NativeGetMyASCFromActor(InActor);

	if (ASC->HasMatchingGameplayTag(TagToRemove))
	{
		ASC->RemoveLooseGameplayTag(TagToRemove);
	}
}

bool UMyBlueprintFunctionLibrary::NativeDoesActorHasTag(AActor* InActor, FGameplayTag TagToCheck)
{
	UMyAbilitySystemComponent* ASC = NativeGetMyASCFromActor(InActor);

	return ASC->HasMatchingGameplayTag(TagToCheck);
}

void UMyBlueprintFunctionLibrary::BP_DoesActorHasTag(AActor* InActor, FGameplayTag TagToCheck, EMyConfirmType& OutConfirmType)
{
	OutConfirmType = NativeDoesActorHasTag(InActor, TagToCheck) ? EMyConfirmType::Yes : EMyConfirmType::No;
}

UPawnCombatComponent* UMyBlueprintFunctionLibrary::NativeGetPawnCombatComponentFromActor(AActor* InActor)
{
	check(InActor);

	if (IPawnCombatInterface* PawnCombatInterface = Cast<IPawnCombatInterface>(InActor))
	{
		return PawnCombatInterface->GetPawnCombatComponent();
	}

	return nullptr;
}

UPawnCombatComponent* UMyBlueprintFunctionLibrary::BP_GetPawnCombatComponentFromActor(AActor* InActor, EMyVaildType& OutVaildType)
{
	UPawnCombatComponent* PawnCombatComponent = NativeGetPawnCombatComponentFromActor(InActor);

	OutVaildType = PawnCombatComponent ? EMyVaildType::Vaild : EMyVaildType::Invaild;

	return PawnCombatComponent;
}

bool UMyBlueprintFunctionLibrary::IsTargetPawnHostile(APawn* QueryPawn, APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);

	IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId();
	}

	return false;
}

float UMyBlueprintFunctionLibrary::GetScalableFloatValueAtLevel(const FScalableFloat& InScalableFloat, float InLevel)
{
	return InScalableFloat.GetValueAtLevel(InLevel);
}

FGameplayTag UMyBlueprintFunctionLibrary::ComputeHitReactDirectionTag(AActor* InAttacker, AActor* InVictim, float& OuntAngleDifference)
{
	check(InAttacker && InVictim);

	const FVector VictimForward = InVictim->GetActorForwardVector();
	const FVector VictimToAttackerNormalize = (InAttacker->GetActorLocation() - InVictim->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalize);
	OuntAngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalize);

	if (CrossResult.Z < 0)
	{
		OuntAngleDifference *= -1.f;
	}

	if (OuntAngleDifference >= -45.f && OuntAngleDifference < 45.f)
	{
		return MyGamePlayTags::Shared_Status_HitReact_Front;
	}
	else if (OuntAngleDifference >= -135.f && OuntAngleDifference < -45.f)
	{
		return MyGamePlayTags::Shared_Status_HitReact_Left;
	}
	else if (OuntAngleDifference >= 45.f && OuntAngleDifference < 135.f)
	{
		return MyGamePlayTags::Shared_Status_HitReact_Right;	
	}
	else if (OuntAngleDifference < -135.f || OuntAngleDifference >= 135.f)
	{
		return MyGamePlayTags::Shared_Status_HitReact_Back;
	}
	
	return MyGamePlayTags::Shared_Status_HitReact_Front;
}

bool UMyBlueprintFunctionLibrary::IsValidBlock(AActor* InAttacker, AActor* InDefensed)
{
	check(InAttacker && InDefensed);

	const float DotResult = FVector::DotProduct(InAttacker->GetActorForwardVector(), InDefensed->GetActorForwardVector());

	//const FString DebugString = FString::Printf(TEXT("Dot Result : %f"), DotResult);

	//Debug::Print(DebugString);

	return DotResult < -0.2f;
}
