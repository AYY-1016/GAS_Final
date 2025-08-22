// Fill out your copyright notice in the Description page of Project Settings.


#include "AnimInstance/Hero/HeroLinkedAnimLayer.h"
#include "AnimInstance/Hero/HeroAnimInstance.h"

UHeroAnimInstance* UHeroLinkedAnimLayer::GetHeroAnimInstance() const
{
    return Cast<UHeroAnimInstance>(GetOwningComponent()->GetAnimInstance());

}
