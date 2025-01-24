#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "OmegaPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class OMEGA_API AOmegaPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AOmegaPlayerState();

public:

	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override		{ return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const											{ return AttributeSet; }
	
protected:
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
