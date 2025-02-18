﻿#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "OmegaTypes.h"
#include "OmegaAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

template<class T>
using TStaticFuncPtr = typename TBaseStaticDelegateInstance<T, FDefaultDelegateUserPolicy>::FFuncPtr;

struct FEffectProperties;

DECLARE_DELEGATE_RetVal(FGameplayAttribute, FAttributeSignature)

UCLASS()
class OMEGA_API UOmegaAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:

	UOmegaAttributeSet();
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

private:
	
	void GetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& OutEffectProperties);

public:

	TMap<FGameplayTag, TStaticFuncPtr<FGameplayAttribute()>> TagsToAttributes;


	
#pragma region PRIMARY ATTRIBUTES

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Strength;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, Strength)

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Dexterity;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, Dexterity)

	UPROPERTY(BlueprintReadOnly, Category = "Primary Attributes")
	FGameplayAttributeData Intelligence;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, Intelligence)

#pragma endregion

#pragma region SECONDARY ATTRIBUTES

	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, MaxHealth)

	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData MaxMana;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, MaxMana)
	
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData HealthRegeneration;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, HealthRegeneration)
	
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData ManaRegeneration;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, ManaRegeneration)
	
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData PhysicalDamage;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, PhysicalDamage)
	
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData MagicDamage;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, MagicDamage)
	
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData BlockChance;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, BlockChance)
	
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")	
	FGameplayAttributeData CritChance;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, CritChance)
	
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData ArmorResistance;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, ArmorResistance)
	
	UPROPERTY(BlueprintReadOnly, Category = "Secondary Attributes")
	FGameplayAttributeData ElementalResistance;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, ElementalResistance)

	

#pragma endregion
	
	UPROPERTY(BlueprintReadOnly, Category = "Tertiary Attributes")
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, Health)
	
	UPROPERTY(BlueprintReadOnly, Category = "Tertiary Attributes")
	FGameplayAttributeData Mana;
	ATTRIBUTE_ACCESSORS(UOmegaAttributeSet, Mana)
};
