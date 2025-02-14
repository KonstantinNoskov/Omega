#include "OmegaGameplayTags.h"

#include "GameplayTagsManager.h"

FOmegaGameplayTags FOmegaGameplayTags::GameplayTags;

void FOmegaGameplayTags::InitializeNativeGameplayTags()
{
	
#pragma region PRIMARY ATTRIBUTES

	// Strength
	UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Primary.Strength"),
			FString("Defines how much physical damage and health character has")
			);

	// Intelligence
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Intelligence"),
		FString("Defines how much magic damage and mana character has")
		);

	// Dexterity
	UGameplayTagsManager::Get().AddNativeGameplayTag(
		FName("Attributes.Primary.Dexterity"),
		FString("Defines chance to deal critical damage and block damage")
		);

#pragma endregion
#pragma region SECONDARY ATTRIBUTES

	// MaxHealth
	UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.MaxHealth"),
			FString("Max amount of health")
			);

	// MaxMana
	UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Secondary.MaxMana"),
			FString("Max amount of mana")
			);

#pragma endregion
#pragma region TERTIARY ATTRIBUTES

	// Health
	UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Tertiary.Health"),
			FString("Current amount of health")
			);

	// Mana
	UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Attributes.Tertiary.Mana"),
			FString("Current amount of mana")
			);

#pragma endregion
#pragma region ELEMENTAL

	// On Fire
	UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Elemental.Fire.OnFire"),
			FString("Actor stays on fire")
			);

	// Burn
	UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Elemental.Fire.Burn"),
			FString("Actor bruns after he came out of fire")
			);

#pragma endregion
#pragma region MESSAGES

	// Health Potions
	UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.HealthPotion.Small"),
			FString("Small health potion taken")
			);

	
	UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.HealthPotion.Mid"),
			FString("Mid health potion taken")
			);

	// Mana Potions
	UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.ManaPotion.Small"),
			FString("Small Mana potion taken")
			);
	
	UGameplayTagsManager::Get().AddNativeGameplayTag(
			FName("Message.ManaPotion.Mid"),
			FString("Mid Mana potion taken")
			);

#pragma endregion
}
