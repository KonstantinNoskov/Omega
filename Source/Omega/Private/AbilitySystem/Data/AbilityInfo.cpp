// Fill out your copyright notice in the Description page of Project Settings.


#include "AbilitySystem/Data/AbilityInfo.h"

FOmegaAbilityInfo UAbilityInfo::GetAbilityInfoByTag(const FGameplayTag& AbilityTag)
{	
	if (AbilityInfoMap.Contains(AbilityTag))
	{
		return AbilityInfoMap[AbilityTag];
	}
	
	return FOmegaAbilityInfo();
}
