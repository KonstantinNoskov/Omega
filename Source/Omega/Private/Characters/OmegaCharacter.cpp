#include "Characters/OmegaCharacter.h"

#include "AbilitySystemComponent.h"
#include "PaperZDAnimationComponent.h"
#include "Components/OmegaMovementComponent.h"

AOmegaCharacter::AOmegaCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UOmegaMovementComponent>(ACharacter::CharacterMovementComponentName))
{
	PrimaryActorTick.bCanEverTick = false;

	PaperAnimation = CreateDefaultSubobject<UPaperZDAnimationComponent>("PaperZD Animation");

	OmegaMovementComponent = Cast<UOmegaMovementComponent>(GetCharacterMovement());

	OmegaMovementComponent->bConstrainToPlane = true;
	OmegaMovementComponent->SetPlaneConstraintAxisSetting(EPlaneConstraintAxisSetting::Y);
}

void AOmegaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void AOmegaCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);	
}

void AOmegaCharacter::InitAbilityActorInfo() {}

void AOmegaCharacter::InitializeDefaultAttributes(const TSubclassOf<UGameplayEffect>& DefaultAttributesEffect, float Level) const
{
	if (!AbilitySystemComponent)
		{ UE_LOG(LogTemp, Error, TEXT("[%hs]: AbilitySystemComponent is null! Can't initialize initial attributes without it."),__FUNCTION__)	return;	}
	
	if (!DefaultAttributesEffect)
		{ UE_LOG(LogTemp, Error, TEXT("[%hs]: Can't initialize initial attributes cause it's empty! Check for player character default attributes properties."),__FUNCTION__)	return;	}
	
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DefaultAttributesEffect, Level, ContextHandle);
	AbilitySystemComponent->ApplyGameplayEffectSpecToTarget(*SpecHandle.Data, AbilitySystemComponent);
}

bool AOmegaCharacter::ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor)
{
	if (OmegaMovementComponent && OmegaMovementComponent->ProcessConsoleExec(Cmd, Ar, Executor))
	{
		return true;
	}
	
	return Super::ProcessConsoleExec(Cmd, Ar, Executor);
}



