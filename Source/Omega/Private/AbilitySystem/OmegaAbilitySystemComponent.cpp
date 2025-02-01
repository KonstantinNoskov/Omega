#include "AbilitySystem/OmegaAbilitySystemComponent.h"


UOmegaAbilitySystemComponent::UOmegaAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UOmegaAbilitySystemComponent::OnAbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UOmegaAbilitySystemComponent::OnEffectApplied);
}

void UOmegaAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& AppliedEffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	AppliedEffectSpec.GetAllAssetTags(TagContainer);
	
	OnEffectAssetTagsUpdatedDelegate.Broadcast(TagContainer);
}


