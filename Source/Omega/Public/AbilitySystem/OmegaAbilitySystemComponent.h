#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "OmegaAbilitySystemComponent.generated.h"

DECLARE_MULTICAST_DELEGATE_OneParam(FOnEffectAssetTagsUpdatedSignature, const FGameplayTagContainer& /*AssetTags*/)

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OMEGA_API UOmegaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UOmegaAbilitySystemComponent();

protected:

	void OnEffectApplied(UAbilitySystemComponent* AbilitySystemComponent, const FGameplayEffectSpec& AppliedEffectSpec, FActiveGameplayEffectHandle ActiveEffectHandle);

public:
	
	void OnAbilityActorInfoSet();

	void AbilityInputTagHeld(const FGameplayTag& InputTag);
	void AbilityInputTagReleased(const FGameplayTag& InputTag);
	
	FOnEffectAssetTagsUpdatedSignature OnEffectAssetTagsUpdatedDelegate;

#pragma region ABILITIES

	void AddCharacterAbilities(const TArray<TSubclassOf<UGameplayAbility>>& InStartupAbilities);

#pragma endregion
		
	
};
