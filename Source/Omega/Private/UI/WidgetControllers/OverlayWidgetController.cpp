#include "UI/WidgetControllers/OverlayWidgetController.h"

#include "OmegaGameplayTags.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "AbilitySystem/OmegaAttributeSet.h"
#include "OmegaTypes.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "BlueprintLibraries/OmegaFunctionLibrary.h"

void UOverlayWidgetController::BroadcastInitialValues()
{

	const UOmegaAttributeSet* OmegaAttributeSet = CastChecked<UOmegaAttributeSet>(AttributeSet);
	check(AttributeData);

	for (auto& Pair : OmegaAttributeSet->TagsToAttributes)
	{
		FOmegaAttributeInfo AttributeInfo = AttributeData->FindAttributeInfoByTag(Pair.Key);
		AttributeInfo.AttributeValue = Pair.Value().GetNumericValue(OmegaAttributeSet);
		OnAttributeInfoChangedDelegate.Broadcast(AttributeInfo);
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
	
	for (auto& Pair : OmegaAttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda([this, Pair, OmegaAttributeSet](const FOnAttributeChangeData& InData)
		{
			FOmegaAttributeInfo Info = AttributeData->FindAttributeInfoByTag(Pair.Key);
			Info.AttributeValue = Pair.Value().GetNumericValue(OmegaAttributeSet);
			
			OnAttributeInfoChangedDelegate.Broadcast(Info);
		});
	}
	
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