#include "AbilitySystem/OmegaAttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameFramework/Character.h"

UOmegaAttributeSet::UOmegaAttributeSet()
{
	
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

	// Clamping the changed attributes
	if (Data.EvaluatedData.Attribute == GetHealthAttribute()) SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
}

void UOmegaAttributeSet::GetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& OutEffectProperties)
{

	// Source == Causer of the effect, Target == target of the effect (owner of this AS)
	
	OutEffectProperties.EffectContextHandle = Data.EffectSpec.GetContext();

	// Get Source Data
	OutEffectProperties.SourceASC = OutEffectProperties.EffectContextHandle.GetOriginalInstigatorAbilitySystemComponent();
	if (IsValid(OutEffectProperties.SourceASC) && OutEffectProperties.SourceASC->AbilityActorInfo.IsValid() && OutEffectProperties.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		OutEffectProperties.SourceAvatarActor = OutEffectProperties.SourceASC->AbilityActorInfo->AvatarActor.Get();
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

