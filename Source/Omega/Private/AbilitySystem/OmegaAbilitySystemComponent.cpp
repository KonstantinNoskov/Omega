#include "AbilitySystem/OmegaAbilitySystemComponent.h"

#include "OmegaGameplayTags.h"


UOmegaAbilitySystemComponent::UOmegaAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UOmegaAbilitySystemComponent::OnAbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UOmegaAbilitySystemComponent::OnEffectApplied);
	
}

void UOmegaAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InStartupAbilities)
{
	for (TSubclassOf<UGameplayAbility> AbilityClass : InStartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1.f);
		GiveAbilityAndActivateOnce(AbilitySpec);
	}
}


// Broadcast gameplay effect tags. Mostly for widget controller
void UOmegaAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& AppliedEffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	AppliedEffectSpec.GetAllAssetTags(TagContainer);
	
	OnEffectAssetTagsUpdatedDelegate.Broadcast(TagContainer);
}


                      