#include "UI/WidgetControllers/OverlayWidgetController.h"

#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "AbilitySystem/OmegaAttributeSet.h"
#include "BlueprintLibraries/OmegaFunctionLibrary.h"

void UOverlayWidgetController::BroadcastInitialValues()
{
	if (const UOmegaAttributeSet* OmegaAttributeSet = CastChecked<UOmegaAttributeSet>(AttributeSet))
	{
		OnHealthChangedDelegate.Broadcast(OmegaAttributeSet->GetHealth());
		OnMaxHealthChangedDelegate.Broadcast(OmegaAttributeSet->GetMaxHealth());
		OnManaChangedDelegate.Broadcast(OmegaAttributeSet->GetMana());
		OnMaxManaChangedDelegate.Broadcast(OmegaAttributeSet->GetMaxMana());
		OnStrengthChangedDelegate.Broadcast(OmegaAttributeSet->GetStrength());
		OnIntelligenceChangedDelegate.Broadcast(OmegaAttributeSet->GetIntelligence());
		OnDexterityChangedDelegate.Broadcast(OmegaAttributeSet->GetDexterity());
	}
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	// Get Essentials
	UOmegaAbilitySystemComponent* OmegaAbilitySystemComponent = Cast<UOmegaAbilitySystemComponent>(AbilitySystemComponent);
	const UOmegaAttributeSet* OmegaAttributeSet = CastChecked<UOmegaAttributeSet>(AttributeSet);

	// Essentials valid check
	checkf(OmegaAbilitySystemComponent,		TEXT("[%hs]: OmegaAbilitySystemComponent cast is failed!"), __FUNCTION__)
	checkf(OmegaAttributeSet,				TEXT("[%hs]: OmegaAttributeSet cast is failed!"), __FUNCTION__)
	
	//	On Attributes Changed
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAttributeSet->GetHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& InData)
	{
		OnHealthChangedDelegate.Broadcast(InData.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAttributeSet->GetMaxHealthAttribute()).AddLambda([this](const FOnAttributeChangeData& InData)
	{
		OnMaxHealthChangedDelegate.Broadcast(InData.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAttributeSet->GetManaAttribute()).AddLambda([this](const FOnAttributeChangeData& InData)
	{
		OnManaChangedDelegate.Broadcast(InData.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAttributeSet->GetMaxManaAttribute()).AddLambda([this](const FOnAttributeChangeData& InData)
	{
		OnMaxManaChangedDelegate.Broadcast(InData.NewValue);
	});
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAttributeSet->GetStrengthAttribute()).AddLambda([this](const FOnAttributeChangeData& InData)
	{
		OnStrengthChangedDelegate.Broadcast(InData.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAttributeSet->GetIntelligenceAttribute()).AddLambda([this](const FOnAttributeChangeData& InData)
	{
		OnIntelligenceChangedDelegate.Broadcast(InData.NewValue);
	});
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(OmegaAttributeSet->GetDexterityAttribute()).AddLambda([this](const FOnAttributeChangeData& InData)
	{
		OnDexterityChangedDelegate.Broadcast(InData.NewValue);
	});
	

	//	On Asset Tag Container Updated
	OmegaAbilitySystemComponent->OnEffectAssetTagsUpdatedDelegate.AddLambda([this](const FGameplayTagContainer& InAssetTags)
	{
		for (const FGameplayTag& Tag : InAssetTags)
		{
			if (!Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message")))) continue;
			
			const FUIWidgetRow* Row = UOmegaFunctionLibrary::GetDataTableRowByTag<FUIWidgetRow>(WidgetMessageDataTable, Tag);
			if (Row) { MessageWidgetRowDelegate.Broadcast(*Row);	}
			else { UE_LOG(LogTemp, Error, TEXT("[%hs]: Message widget row in %s doesn't exist!"), __FUNCTION__, *WidgetMessageDataTable->GetName()) } 
		}
	});
	
}