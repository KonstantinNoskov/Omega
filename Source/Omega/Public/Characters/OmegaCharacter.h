#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "OmegaCharacter.generated.h"

class UAttributeSet;
class UAbilitySystemComponent;
class UPaperZDAnimationComponent;

UCLASS()
class OMEGA_API AOmegaCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:

	AOmegaCharacter();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PaperZD", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperZDAnimationComponent> PaperAnimation; 

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
