#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "OmegaAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class OMEGA_API UOmegaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UOmegaAttributeSet();

	UPROPERTY(BlueprintReadOnly, Category = "Tertiary Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, Health)

	UPROPERTY(BlueprintReadOnly, Category = "Tertiary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Tertiary Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, Mana)

	UPROPERTY(BlueprintReadOnly, Category = "Tertiary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, MaxMana)
};
