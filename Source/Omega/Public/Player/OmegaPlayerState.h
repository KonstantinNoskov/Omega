#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "OmegaPlayerState.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class OMEGA_API AOmegaPlayerState : public APlayerState
{
	GENERATED_BODY()


	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
