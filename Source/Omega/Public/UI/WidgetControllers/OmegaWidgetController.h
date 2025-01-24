#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "OmegaWidgetController.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class OMEGA_API UOmegaWidgetController : public UObject
{
	GENERATED_BODY()

	

public:

	void SetWidgetControllerParameters();

protected:

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category = "Widget Controller")
	TObjectPtr<UAttributeSet> AttributeSet;
	
};
