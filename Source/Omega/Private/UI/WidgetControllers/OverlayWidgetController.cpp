#include "UI/WidgetControllers/OverlayWidgetController.h"

#include "AbilitySystem/OmegaAttributeSet.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	if (const UOmegaAttributeSet* OmegaAttributeSet = CastChecked<UOmegaAttributeSet>(AttributeSet))
	{
		OnHealthChangedDelegate.Broadcast(OmegaAttributeSet->GetHealth());
		OnMaxHealthChangedDelegate.Broadcast(OmegaAttributeSet->GetMaxHealth());
		OnManaChangedDelegate.Broadcast(OmegaAttributeSet->GetMana());
		OnMaxManaChangedDelegate.Broadcast(OmegaAttributeSet->GetMaxMana());
	}
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	if (const UOmegaAttributeSet* OmegaAttributeSet = CastChecked<UOmegaAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAttributeSet->GetHealthAttribute()).AddUObject		(this,	&UOverlayWidgetController::OnHealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAttributeSet->GetMaxHealthAttribute()).AddUObject	(this,	&UOverlayWidgetController::OnMaxHealthChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAttributeSet->GetManaAttribute()).AddUObject		(this,	&UOverlayWidgetController::OnManaChanged);
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAttributeSet->GetMaxManaAttribute()).AddUObject	(this,	&UOverlayWidgetController::OnMaxManaChanged);
	}
}

#pragma region ON ATTRIBUTES CHANGED CALLBACKS

void UOverlayWidgetController::OnHealthChanged(const FOnAttributeChangeData& InData)		const		{	OnHealthChangedDelegate.Broadcast		(InData.NewValue);	}
void UOverlayWidgetController::OnMaxHealthChanged(const FOnAttributeChangeData& InData)		const		{	OnMaxHealthChangedDelegate.Broadcast	(InData.NewValue);	}
void UOverlayWidgetController::OnManaChanged(const FOnAttributeChangeData& InData)			const		{	OnManaChangedDelegate.Broadcast			(InData.NewValue);	}
void UOverlayWidgetController::OnMaxManaChanged(const FOnAttributeChangeData& InData)		const		{	OnMaxManaChangedDelegate.Broadcast		(InData.NewValue);	}

#pragma endregion

