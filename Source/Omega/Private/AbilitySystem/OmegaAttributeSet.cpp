﻿#include "AbilitySystem/OmegaAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "OmegaGameplayTags.h"
#include "Characters/OmegaCharacter.h"
#include "GameFramework/Character.h"
#include "Interfaces/CombatInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Player/OmegaPlayerController.h"

UOmegaAttributeSet::UOmegaAttributeSet()
{
	const FOmegaGameplayTags GameplayTags = FOmegaGameplayTags::Get();
	
	// Primary Attributes
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Strength,		GetStrengthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Intelligence,	GetIntelligenceAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Primary_Dexterity,		GetDexterityAttribute);
	
	// Secondary Attributes
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxHealth,	GetMaxHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Secondary_MaxMana,		GetMaxManaAttribute);

	// Tertiary Attributes
	TagsToAttributes.Add(GameplayTags.Attributes_Tertiary_Health,		GetHealthAttribute);
	TagsToAttributes.Add(GameplayTags.Attributes_Tertiary_Mana,			GetManaAttribute);
	
}

void UOmegaAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetHealthAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	if (Attribute == GetManaAttribute()) NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMana());
}

void UOmegaAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	FEffectProperties EffectProperties;
	GetEffectProperties(Data, EffectProperties);

	// Clamping Health
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));

		UE_LOG(LogTemp, Warning, TEXT("[%hs] %f %s "), __FUNCTION__, GetHealth(), *EffectProperties.TargetCharacter->GetName());
	}

	// Clamping Mana
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		SetMana(FMath::Clamp(GetMana(), 0.f, GetMaxMana()));

		UE_LOG(LogTemp, Warning, TEXT("[%hs] %f "), __FUNCTION__, GetMana());
	}

	// Handle Incoming Damage
	if (Data.EvaluatedData.Attribute == GetDamageAttribute())
	{
		const float LocalIncomingDamage = GetDamage();
		SetDamage(0.f);
		
		if (LocalIncomingDamage > 0.f)
		{
			// Clamp Updated Health
			const float NewHealth = GetHealth() - LocalIncomingDamage;
			SetHealth(FMath::Clamp(NewHealth, 0.f, GetMaxHealth()));

			// Check for fatal damage
			const bool bFatal = NewHealth <= 0.f;

			// Perform Hit Reaction 
			if (bFatal)
			{
				if (EffectProperties.TargetAvatarActor->Implements<UCombatInterface>())
				{
					ICombatInterface::Execute_Die(EffectProperties.TargetAvatarActor);
				}
			}
			else
			{
				FGameplayTagContainer TagContainer;
				TagContainer.AddTag(FOmegaGameplayTags::Get().Effects_HitReact);
				EffectProperties.TargetASC->TryActivateAbilitiesByTag(TagContainer);
			}

			// Show Damage Widget

			if (EffectProperties.SourceCharacter != EffectProperties.TargetCharacter)
			{
				AOmegaPlayerController* OmegaPC = Cast<AOmegaPlayerController>(UGameplayStatics::GetPlayerController(EffectProperties.SourceCharacter, 0));
				if(OmegaPC)
				{	
					OmegaPC->ShowDamageNumber(LocalIncomingDamage, EffectProperties.TargetCharacter);
				}				
			}
		}
	}
}

void UOmegaAttributeSet::GetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& OutEffectProperties)
{

	// Source == Causer of the effect, Target == target of the effect (owner of this AS)
	
	OutEffectProperties.EffectContextHandle = Data.EffectSpec.GetContext();

	// Get Source Data
	OutEffectProperties.SourceASC = OutEffectProperties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(OutEffectProperties.SourceASC) && OutEffectProperties.SourceASC->AbilityActorInfo.IsValid() && OutEffectProperties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		// Get Source Avatar Actor
		OutEffectProperties.SourceAvatarActor = OutEffectProperties.SourceASC->AbilityActorInfo->AvatarActor.Get();

		// Get Source Controller
		OutEffectProperties.SourceController = OutEffectProperties.SourceASC->AbilityActorInfo->PlayerController.Get();
		
		if (OutEffectProperties.SourceController && OutEffectProperties.SourceAvatarActor)
		{
			if (const APawn* Pawn = Cast<APawn>(OutEffectProperties.SourceAvatarActor))
			{
				OutEffectProperties.SourceController = Pawn->GetController();
			}
		}

		if (OutEffectProperties.SourceController)
		{
			ACharacter* SourceCharacter = Cast<ACharacter>(OutEffectProperties.SourceController->GetPawn());
			OutEffectProperties.SourceCharacter = SourceCharacter;
		}
	}

	// Get Target Data
	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		OutEffectProperties.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		OutEffectProperties.TargetController = Data.Target.AbilityActorInfo->PlayerController.Get();
		OutEffectProperties.TargetCharacter = Cast<ACharacter>(OutEffectProperties.TargetAvatarActor);
		OutEffectProperties.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OutEffectProperties.TargetAvatarActor);
	}
}

