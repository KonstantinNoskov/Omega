#include "Characters/OmegaCharacter.h"

#include "AbilitySystemComponent.h"
#include "PaperZDAnimationComponent.h"

AOmegaCharacter::AOmegaCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	PaperAnimation = CreateDefaultSubobject<UPaperZDAnimationComponent>("PaperZD Animation");
}

void AOmegaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AOmegaCharacter::InitAbilityActorInfo() {}


void AOmegaCharacter::InitializeDefaultAttributes(const TSubclassOf<UGameplayEffect>& DefaultAttributesEffect, float Level) const
{
	if (!AbilitySystemComponent)
		{ UE_LOG(LogTemp, Error, TEXT("[%hs]: AbilitySystemComponent is null! Can't initialize primary attributes without it."),__FUNCTION__)	return;	}
	
	if (!DefaultAttributesEffect)
		{ UE_LOG(LogTemp, Error, TEXT("[%hs]: Can't initialize default attributes cause it's empty! Check for player character default attributes properties."),__FUNCTION__)	return;	}
	
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributesEffect, Level, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, AbilitySystemComponent);
}

