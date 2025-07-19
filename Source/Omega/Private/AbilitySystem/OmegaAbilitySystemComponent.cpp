#include "AbilitySystem/OmegaAbilitySystemComponent.h"

#include "OmegaGameplayTags.h"
#include "AbilitySystem/Abilities/OmegaGameplayAbility.h"
#include "Characters/OmegaCharacter.h"
#include "Components/OmegaMovementComponent.h"
#include "UI/WidgetControllers/OverlayWidgetController.h"



UOmegaAbilitySystemComponent::UOmegaAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UOmegaAbilitySystemComponent::OnAbilityActorInfoSet()
{
	OnGameplayEffectAppliedDelegateToSelf.AddUObject(this, &UOmegaAbilitySystemComponent::OnEffectApplied);
}

void UOmegaAbilitySystemComponent::AbilityInputTagPressed(const FGameplayTag& InputTag)
{

	if (!InputTag.IsValid()) return;

	if (GetOmegaMovementComponent()->GetOmegaCustomMovementMode() != EOmegaCustomMovementMode::NONE) return;
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) || AbilitySpec.IsActive()) continue;
		
		
		AbilitySpecInputPressed(AbilitySpec);
		
		TryActivateAbility(AbilitySpec.Handle);
	}
}

void UOmegaAbilitySystemComponent::AbilityInputTagHeld(const FGameplayTag& InputTag)
{
	/*if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag) || AbilitySpec.IsActive()) return;

		AbilitySpecInputPressed(AbilitySpec);
		TryActivateAbility(AbilitySpec.Handle);
	}*/
}

void UOmegaAbilitySystemComponent::AbilityInputTagReleased(const FGameplayTag& InputTag)
{
	if (!InputTag.IsValid()) return;

	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InputTag)) return;
		
		AbilitySpecInputReleased(AbilitySpec);
	}
}

void UOmegaAbilitySystemComponent::AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InStartupAbilities)
{
	for (const TSubclassOf<UGameplayAbility> AbilityClass : InStartupAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1.f);
		
		if (const UOmegaGameplayAbility* OmegaAbility = CastChecked<UOmegaGameplayAbility>(AbilitySpec.Ability))
		{
			AbilitySpec.DynamicAbilityTags.AddTag(OmegaAbility->StartupInputTag);
			GiveAbility(AbilitySpec);
		}
	}

	bStartupAbilitiesGranted = true;
	OnAbilityGrantedDelegate.Broadcast(this);
}

void UOmegaAbilitySystemComponent::ForEachAbility(const FForEachAbility& InDelegate)
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!InDelegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogClass, Warning, TEXT("Failed to execute delegate in %hs"), __FUNCTION__)	
		}
	}
}



FGameplayTag UOmegaAbilitySystemComponent::GetAbilityTagBySpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!AbilitySpec.Ability) return FGameplayTag::EmptyTag; 

	for (FGameplayTag Tag : AbilitySpec.Ability.Get()->AbilityTags)
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities"))))
		{
			return Tag;
		}
	}
	
	return FGameplayTag::EmptyTag;
}

FGameplayTag UOmegaAbilitySystemComponent::GetInputTagBySpec(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!AbilitySpec.Ability) return FGameplayTag::EmptyTag; 

	for (FGameplayTag Tag : AbilitySpec.DynamicAbilityTags)
	{
		if (Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Input"))))
		{
			return Tag;
		}
	}
	
	return FGameplayTag::EmptyTag;
}


// Broadcast gameplay effect tags. Mostly for widget controller
void UOmegaAbilitySystemComponent::OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& AppliedEffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle)
{
	FGameplayTagContainer TagContainer;
	AppliedEffectSpec.GetAllAssetTags(TagContainer);
	
	OnEffectAssetTagsUpdatedDelegate.Broadcast(TagContainer, AppliedEffectSpec);
}

UOmegaMovementComponent* UOmegaAbilitySystemComponent::GetOmegaMovementComponent()
{
	if (!OmegaMovementComponent)
	{
		if (AOmegaCharacter* OmegaCharacter = Cast<AOmegaCharacter>(GetAvatarActor()))
		{
			OmegaMovementComponent = OmegaCharacter->GetOmegaMovementComponent();
		}
	}
	
	return OmegaMovementComponent;
}

void UOmegaAbilitySystemComponent::OnAbilityGrantedBySpec(const FGameplayAbilitySpec& AbilitySpec)
{
	
}