#include "BlueprintLibraries/OmegaFunctionLibrary.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayAbilitySpec.h"
#include "PaperSprite.h"
#include "AbilitySystem/Data/CharacterDefaultInfo.h"
#include "Game/GameModes/OmegaGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "AbilitySystemComponent.h"
#include "OmegaAbilityTypes.h"
#include "OmegaGameplayTags.h"
#include "AbilitySystem/Data/DamageWidgetInfo.h"
#include "Engine/CoreSettings.h"
#include "Engine/OverlapResult.h"
#include "Game/SaveGame/LoadMenuSaveGame.h"
#include "Interfaces/CombatInterface.h"

/*FVector2D UOmegaFunctionLibrary::GetSourceSize(UPaperSprite* Sprite)
{
	return Sprite->GetSourceSize();
}*/

void UOmegaFunctionLibrary::GiveStartupAbilities(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, const FGameplayTag& CharacterAttackType)
{
	// Check for GameMode
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!OmegaGameMode) return;

	// Check for Character Class Info 
	if (!OmegaGameMode->CharacterClassInfo)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Character Class Info is null. Check for game mode defaults."), __FUNCTION__);
		return;
	}
	
	UCharacterDefaultInfo* CharacterClassInfo = OmegaGameMode->CharacterClassInfo;
	
	// Assign common abilities
	for (const TSubclassOf<UGameplayAbility> AbilityClass : CharacterClassInfo->CommonAbilities)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, 1);
		ASC->GiveAbility(AbilitySpec);
	}

	// Assign Character class abilities
	for (auto AbilityClass : CharacterClassInfo->CharacterClassAbilities)
	{
		ICombatInterface* CombatInterface = Cast<ICombatInterface>(ASC->GetAvatarActor());
		if (CombatInterface)
		{
			FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass.Value, CombatInterface->GetPlayerLevel());
			ASC->GiveAbility(AbilitySpec);
		}
	}
}
void UOmegaFunctionLibrary::ModifyAttributesByTag(const UObject* WorldContextObject, const FGameplayTagContainer& InTagContainer, UAbilitySystemComponent* ASC)
{
	// Check for GameMode
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!OmegaGameMode) return;

	// Check for Character Class Info 
	if (!OmegaGameMode->CharacterClassInfo)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Character Class Info is null. Check for game mode defaults."), __FUNCTION__);
		return;
	}
	
	// Modify ASC attributes if character
	UCharacterDefaultInfo* CharacterClassInfo = OmegaGameMode->CharacterClassInfo;

	
	for (const FGameplayTag& ModifyTag : InTagContainer)
	{
		if (CharacterClassInfo->CharacterTypeInfo.Contains(ModifyTag))
		{
			checkf(CharacterClassInfo->CharacterTypeInfo.Contains(ModifyTag), TEXT("%hs: Attribute modifier tag in CharacterClassInfo is empty!"), __FUNCTION__)

			// Apply attributes modify effect by Character tag 
			const TSubclassOf<UGameplayEffect>& AttributeModifyEffect = CharacterClassInfo->GetCharacterTypeInfo(ModifyTag).AttributesModifyEffect;
			FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
			FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(AttributeModifyEffect, 1.f, EffectContextHandle); 
			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
		}
	}
}

bool UOmegaFunctionLibrary::IsImmuneToEffect(const FGameplayEffectContextHandle& ContextHandle)
{
	if (const FOmegaGameplayEffectContext* OmegaContext = static_cast<const FOmegaGameplayEffectContext*>(ContextHandle.Get()))
	{
		return OmegaContext->IsImmune();
	}
	
	return false;
}
void UOmegaFunctionLibrary::SetIsImmuneToEffect(FGameplayEffectContextHandle& ContextHandle, bool bIsImmuneToEffect)
{
	if (FOmegaGameplayEffectContext* OmegaContext = static_cast<FOmegaGameplayEffectContext*>(ContextHandle.Get()))
	{
		OmegaContext->SetIsImmune(bIsImmuneToEffect);
	}
}

bool UOmegaFunctionLibrary::IsBlockedEffect(const FGameplayEffectContextHandle& ContextHandle)
{
	if (const FOmegaGameplayEffectContext* OmegaContext = static_cast<const FOmegaGameplayEffectContext*>(ContextHandle.Get()))
	{
		return OmegaContext->IsBlocked();
	}
	
	return false;
}
bool UOmegaFunctionLibrary::IsParryEffect(const FGameplayEffectContextHandle& ContextHandle)
{
	if (const FOmegaGameplayEffectContext* OmegaContext = static_cast<const FOmegaGameplayEffectContext*>(ContextHandle.Get()))
	{
		return OmegaContext->IsParried();
	}
	
	return false;
}

void UOmegaFunctionLibrary::GetAlivePlayersWithinBox(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& IgnoredActors, const FVector& BoxExtent,
                                                     const FVector& BoxOrigin)
{
	FCollisionQueryParams BoxParams;
	BoxParams.AddIgnoredActors(IgnoredActors);
	
	TArray<FOverlapResult> Overlaps;
	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		bool bHit = World->OverlapMultiByObjectType(Overlaps, BoxOrigin, FQuat::Identity, FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects), FCollisionShape::MakeBox(BoxExtent), BoxParams);
		//if (!bHit) return;
		
		for (const FOverlapResult& OverlappedActor : Overlaps)
		{
			if (OverlappedActor.GetActor()->Implements<UCombatInterface>())
			{
				bool bDead = ICombatInterface::Execute_IsDead(OverlappedActor.GetActor());
				if (bDead) continue;
				OutOverlappingActors.AddUnique(OverlappedActor.GetActor());
			}
		}
	}
}

const FColor& UOmegaFunctionLibrary::GetDamageTypeColorByTag(const UObject* WorldContextObject, FGameplayTag GameplayTag)
{
	// Check for GameMode
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	if (!OmegaGameMode) return FColor::Black; 

	// Check for Character Class Info 
	if (!OmegaGameMode->DamageWidgetData)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Damage Widget Data is null. Check for game mode defaults."), __FUNCTION__);
		return FColor::Black;
	}
	
	UDamageWidgetData* DamageWidgetData = OmegaGameMode->DamageWidgetData;
	
	return DamageWidgetData ? DamageWidgetData->GetDamageTypeColorByTag(GameplayTag) : FColor::Black;
}

void UOmegaFunctionLibrary::InitializeDefaultAttributes(const UObject* WorldContextObject, UAbilitySystemComponent* ASC)
{
	AActor* AvatarActor = ASC->GetAvatarActor();
	
	UCharacterDefaultInfo* CharacterDefaultInfo = GetCharacterDefaultInfo(WorldContextObject);
	if (!IsValid(CharacterDefaultInfo->DefaultPrimaryAttribute))
	{ UE_LOG(LogClass, Warning, TEXT("[%hs]: Character default primary attribute info is null. Check for Character Default Info settings."), __FUNCTION__) return; }
	
	FGameplayEffectContextHandle PrimaryAttributesContextHandle = ASC->MakeEffectContext();
	PrimaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle PrimaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterDefaultInfo->DefaultPrimaryAttribute, 1, PrimaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*PrimaryAttributesSpecHandle.Data.Get());

	if (!IsValid(CharacterDefaultInfo->DefaultSecondaryAttribute))
	{ UE_LOG(LogClass, Warning, TEXT("[%hs]: Character default secondary attribute info is null. Check for Character Default Info settings."), __FUNCTION__) return; }
	FGameplayEffectContextHandle SecondaryAttributesContextHandle = ASC->MakeEffectContext();
	SecondaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle SecondaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterDefaultInfo->DefaultSecondaryAttribute, 1, SecondaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*SecondaryAttributesSpecHandle.Data.Get());

	if (!IsValid(CharacterDefaultInfo->DefaultSecondaryAttribute))
	{ UE_LOG(LogClass, Warning, TEXT("[%hs]: Character default tertiary attribute info is null. Check for Character Default Info settings."), __FUNCTION__) return; }
	FGameplayEffectContextHandle TertiaryAttributesContextHandle = ASC->MakeEffectContext();
	TertiaryAttributesContextHandle.AddSourceObject(AvatarActor);
	const FGameplayEffectSpecHandle TertiaryAttributesSpecHandle = ASC->MakeOutgoingSpec(CharacterDefaultInfo->DefaultTertiaryAttribute, 1, TertiaryAttributesContextHandle);
	ASC->ApplyGameplayEffectSpecToSelf(*TertiaryAttributesSpecHandle.Data.Get());	
}

void UOmegaFunctionLibrary::InitializeAttributesFromSaveData(const UObject* WorldContextObject, UAbilitySystemComponent* ASC, ULoadMenuSaveGame* SaveGame)
{
	UCharacterDefaultInfo* CharacterDefaultInfo = GetCharacterDefaultInfo(WorldContextObject);
	if (!IsValid(CharacterDefaultInfo->DefaultPrimaryAttribute))
	{ UE_LOG(LogClass, Warning, TEXT("[%hs]: Character default primary attribute info is null. Check for Character Default Info settings."), __FUNCTION__) return; }

	AActor* AvatarActor = ASC->GetAvatarActor();
	const FOmegaGameplayTags& GameplayTags = FOmegaGameplayTags::Get();

	FGameplayEffectContextHandle EffectContextHandle = ASC->MakeEffectContext();
	EffectContextHandle.AddSourceObject(AvatarActor);

	FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(CharacterDefaultInfo->SetByCallerPrimaryAttribute, 1, EffectContextHandle);

	// Apply primary attributes from save game.
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Primary_Strength,		SaveGame->Strength);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Primary_Intelligence,	SaveGame->Intelligence);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Primary_Dexterity,		SaveGame->Dexterity);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Secondary_MaxHealth,	SaveGame->MaxHealth);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Tertiary_Health,		SaveGame->Health);
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	
	// Apply secondary attributes from save game.
	SpecHandle = ASC->MakeOutgoingSpec(CharacterDefaultInfo->SetByCallerSecondaryAttribute, 1, EffectContextHandle);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Secondary_MaxHealth,	SaveGame->MaxHealth);
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);

	// Apply tertiary attributes from save game.
	SpecHandle = ASC->MakeOutgoingSpec(CharacterDefaultInfo->SetByCallerTertiaryAttribute, 1, EffectContextHandle);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GameplayTags.Attributes_Tertiary_Health,		SaveGame->Health);
	ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
}

UCharacterDefaultInfo* UOmegaFunctionLibrary::GetCharacterDefaultInfo(const UObject* WorldContextObject)
{
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(WorldContextObject));
	return OmegaGameMode->CharacterClassInfo;;
}
