#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PaperCharacter.h"
#include "Interfaces/CombatInterface.h"

#include "OmegaCharacter.generated.h"

class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;
class UPaperZDAnimationComponent;

UCLASS()
class OMEGA_API AOmegaCharacter : public APaperCharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:

	AOmegaCharacter();

protected:

	virtual void BeginPlay() override;

public:

	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override		{ return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const											{ return AttributeSet; }


protected:
	
	/**
	 * Assign owner & avatar actor to Ability system 
	 */
	virtual void InitAbilityActorInfo();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PaperZD", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperZDAnimationComponent> PaperAnimation; 

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;


#pragma region ATTRIBUTES

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	void InitializeDefaultAttributes(const TSubclassOf<UGameplayEffect>& DefaultAttributesEffect, float Level) const;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default Attributes", DisplayName = "Primary Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default Attributes", DisplayName = "Secondary Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default Attributes", DisplayName = "Tertiary Attributes")
	TSubclassOf<UGameplayEffect> DefaultTertiaryAttributes;

#pragma endregion
	
};
