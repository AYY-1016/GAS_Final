// Fill out your copyright notice in the Description page of Project Settings.


#include "DataAsset/Input/DataAsset_InputConfig.h"

UInputAction* UDataAsset_InputConfig::FindInputActionByTag(const FGameplayTag& IntputTag) const
{
	for (const FMyGameInputActionConfig& InputActionConfig : NativeInputActions) {
		if (InputActionConfig.InputTag == IntputTag && InputActionConfig.InputAction) {
			return InputActionConfig.InputAction;
		}
	}
	return nullptr;
}
