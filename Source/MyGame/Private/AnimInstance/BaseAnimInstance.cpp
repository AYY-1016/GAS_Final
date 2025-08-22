// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/BaseAnimInstance.h"
#include "MyBlueprintFunctionLibrary.h"

bool UBaseAnimInstance::DoesOwnerHaveTag(FGameplayTag TagtoCheck) const
{
    if (APawn* OwningPawn = TryGetPawnOwner())
    {
        return UMyBlueprintFunctionLibrary::NativeDoesActorHasTag(OwningPawn, TagtoCheck);
    }
    return false;
}
