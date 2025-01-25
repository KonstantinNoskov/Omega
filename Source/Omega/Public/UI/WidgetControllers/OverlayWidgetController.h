#pragma once

#include "CoreMinimal.h"
#include "OmegaWidgetController.h"
#include "OverlayWidgetController.generated.h"


struct FOnAttributeChangeData;

UCLASS()
class OMEGA_API UOverlayWidgetController : public UOmegaWidgetController
{
	GENERATED_BODY()

public:
	
	virtual void BroadcastInitialValues() override;
	virtual void BindCallbacksToDependencies() override;

protected:

	void OnHealthChanged(const FOnAttributeChangeData& InData) const;
	void OnMaxHealthChanged(const FOnAttributeChangeData& InData) const;
	void OnManaChanged(const FOnAttributeChangeData& InData) const;
	void OnMaxManaChanged(const FOnAttributeChangeData& InData) const;
	

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeValueChangedSignature OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeValueChangedSignature OnMaxHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeValueChangedSignature OnManaChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GAS|Attributes")
	FOnAttributeValueChangedSignature OnMaxManaChangedDelegate;
};
