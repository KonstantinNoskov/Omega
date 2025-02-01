#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PaperCharacter.h"

#include "OmegaCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UPaperZDAnimationComponent;

UCLASS()
class OMEGA_API AOmegaCharacter : public APaperCharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AOmegaCharacter();

protected:

	virtual void BeginPlay() override;

public:

	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override		{ return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const											{ return AttributeSet; }


protected:
	
	/**
	 * Assign owner & avatar actor to Ability system 
	 */
	virtual void InitAbilityActorInfo();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PaperZD", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperZDAnimationComponent> PaperAnimation; 

protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;


};
