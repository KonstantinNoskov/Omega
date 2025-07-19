﻿#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OmegaFunctionLibrary.generated.h"

struct FGameplayEffectContextHandle;
class ULoadMenuSaveGame;
class UCharacterDefaultInfo;
class UAbilitySystemComponent;
struct FGameplayTag;
class UPaperSprite;

UCLASS()
class OMEGA_API UOmegaFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	template <typename T>
	static T* GetDataTableRowByTag(UDataTable* InDataTable, const FGameplayTag& InTag)
	{
		return InDataTable->FindRow<T>(InTag.GetTagName(), TEXT(""));
	}
	
	/**
	 * 
	 * @param Sprite 
	 * @return 
	 */
	/*UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Source Size", Keywords = "Source Texture Sprite"), Category = "Omega|StaticFunctions")
	static FVector2D GetSourceSize(UPaperSprite* Sprite);*/


	/**
	 * 
	 * @param WorldContextObject 
	 * @param ASC
	 * @param CharacterAttackType 
	 */
	UFUNCTION(BlueprintCallable, Category = "Omega Function Library|Character Class Defaults")
	static void GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, const FGameplayTag& CharacterAttackType = FGameplayTag());

	/**
	 * 
	 * @param WorldContextObject
	 * @param InTagContainer
	 * @param ASC 
	 */
	UFUNCTION(BlueprintCallable, Category = "Omega Function Library|Character Class Defaults")
	static void ModifyAttributesByTag(const UObject* WorldContextObject, const FGameplayTagContainer& InTagContainer, UAbilitySystemComponent* ASC);

	/**
	 * 
	 * @param ContextHandle
	 *
	 * @return true if attribute set is immune to a gameplay effect  
	 */
	UFUNCTION(BlueprintPure, Category = "Omega Ability System Library")
	static bool IsImmuneToEffect(const FGameplayEffectContextHandle& ContextHandle);

	/**
	 *	Set Immune to effect status
	 */
	UFUNCTION(BlueprintCallable, Category = "Omega Ability System Library")
	static void SetIsImmuneToEffect(UPARAM(ref) FGameplayEffectContextHandle& ContextHandle, bool bIsImmuneToEffect);

	/**
	 * @param ContextHandle
	 *
	 * @return true if 
	 */
	UFUNCTION(BlueprintPure, Category = "Omega Ability System Library")
	static bool IsBlockedEffect(const FGameplayEffectContextHandle& ContextHandle);

	/**
	 * @param ContextHandle
	 *
	 * @return true if 
	 */
	UFUNCTION(BlueprintPure, Category = "Omega Ability System Library")
	static bool IsParryEffect(const FGameplayEffectContextHandle& ContextHandle);

	/**
	 * @param 
	 *
	 * @return 
	 */
	UFUNCTION(BlueprintPure, Category = "Omega Ability System Library")
	static void GetAlivePlayersWithinBox(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& IgnoredActors, const FVector& BoxExtent,
	                                     const FVector& BoxOrigin);

	/**
	 * @param ContextHandle
	 * @param GameplayTag
	 *
	 * @return true if 
	 */
	UFUNCTION(BlueprintPure, Category = "Omega Ability System Library", meta = (DefaultToSelf = "WorldContextObject"))
	static const FColor& GetDamageTypeColorByTag(const UObject* WorldContextObject, FGameplayTag GameplayTag);

	UFUNCTION(Category = "Omega Ability System Library", meta = (DefaultToSelf = "WorldContextObject"))
	static void InitializeDefaultAttributes(const UObject* WorldContextObject, UAbilitySystemComponent* ASC);

	UFUNCTION(Category = "Omega Ability System Library", meta = (DefaultToSelf = "WorldContextObject"))
	static void InitializeAttributesFromSaveData(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ULoadMenuSaveGame* SaveGame);
	
	UFUNCTION(BlueprintPure, Category = "Omega Ability System Library", meta = (DefaultToSelf = "WorldContextObject"))
	static UCharacterDefaultInfo* GetCharacterDefaultInfo(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category = "Omega Ability System Library", meta = (DefaultToSelf = "WorldContextObject"))
	static UTexture2D* GetInputIconByTag(const UObject* WorldContextObject, FGameplayTag GameplayTag);
	
};
