#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"


/**
 * OmegaGameplayTags
 *
 * Singleton containing native Gameplay Tags
 */

struct FOmegaGameplayTags
{
	

	static const FOmegaGameplayTags& Get() { return GameplayTags; }
	static void InitializeNativeGameplayTags();

private:

	static FOmegaGameplayTags GameplayTags;
	

public:

#pragma region PRIMARY ATTRIBUTE
	
	FGameplayTag Attributes_Primary_Strength;
	FGameplayTag Attributes_Primary_Intelligence;
	FGameplayTag Attributes_Primary_Dexterity;

#pragma endregion

#pragma region SECONDARY ATTRIBUTE
	
	FGameplayTag Attributes_Secondary_MaxHealth;
	FGameplayTag Attributes_Secondary_MaxMana;

#pragma endregion

#pragma region TERTIARY ATTRIBUTE


	FGameplayTag Attributes_Tertiary_Health;
	FGameplayTag Attributes_Tertiary_Mana;

#pragma endregion

#pragma region ELEMENTALS
	
	FGameplayTag Elemental_Fire_OnFire;
	FGameplayTag Elemental_Fire_Burn;

	FGameplayTag Elemental_Water_InWater;
	FGameplayTag Elemental_Water_Wet;
	

#pragma endregion

#pragma region MESSAGES
	
	FGameplayTag Message_HealthPotion_Small;
	FGameplayTag Message_HealthPotion_Mid;
	
	FGameplayTag Message_ManaPotion_Small;
	FGameplayTag Message_ManaPotion_Mid; 

#pragma endregion 


#pragma region INPUT

	FGameplayTag InputTag_LMB;
	FGameplayTag InputTag_RMB;

#pragma endregion


};

