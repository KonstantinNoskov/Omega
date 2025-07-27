#include "UI/WidgetControllers/OverlayWidgetController.h"

#include "OmegaGameplayTags.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "AbilitySystem/OmegaAttributeSet.h"
#include "OmegaTypes.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "AbilitySystem/Data/AttributeInfo.h"
#include "BlueprintLibraries/OmegaFunctionLibrary.h"

void UOverlayWidgetController::BroadcastInitialValues()
{

	const UOmegaAttributeSet* OmegaAttributeSet = CastChecked<UOmegaAttributeSet>(AttributeSet);
	if (!AttributeData) return;
	
	for (auto& Pair : OmegaAttributeSet->TagsToAttributes)
	{
		FOmegaAttributeInfo AttributeInfo = AttributeData->FindAttributeInfoByTag(Pair.Key);
		AttributeInfo.AttributeValue = Pair.Value().GetNumericValue(OmegaAttributeSet);
		OnAttributeInfoChangedDelegate.Broadcast(AttributeInfo);
	}
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	// Essentials valid check
	UOmegaAbilitySystemComponent* OmegaAbilitySystemComponent = Cast<UOmegaAbilitySystemComponent>(AbilitySystemComponent);
	const UOmegaAttributeSet* OmegaAttributeSet = CastChecked<UOmegaAttributeSet>(AttributeSet);
	checkf(OmegaAbilitySystemComponent,		TEXT("[%hs]: OmegaAbilitySystemComponent cast is failed!"), __FUNCTION__)
	checkf(OmegaAttributeSet,				TEXT("[%hs]: OmegaAttributeSet cast is failed!"), __FUNCTION__)

	// Bind callbacks to all existing attributes
	for (auto& Pair : OmegaAttributeSet->TagsToAttributes)
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Value()).AddLambda([this, Pair, OmegaAttributeSet](const FOnAttributeChangeData& InData)
		{
			FOmegaAttributeInfo Info = AttributeData->FindAttributeInfoByTag(Pair.Key);
			Info.AttributeValue = Pair.Value().GetNumericValue(OmegaAttributeSet);
			
			OnAttributeInfoChangedDelegate.Broadcast(Info);
		});
	}

	// Bind callbacks to Ability updates
	if (OmegaAbilitySystemComponent->bStartupAbilitiesGranted)
	{
		OnInitializeStartupAbilities(OmegaAbilitySystemComponent);
	}
	else
	{
		OmegaAbilitySystemComponent->OnAbilityGrantedDelegate.AddUObject(this, &UOverlayWidgetController::OnInitializeStartupAbilities);
		OmegaAbilitySystemComponent->OnAbilityGrantedBySpecDelegate.AddUObject(this, &UOverlayWidgetController::OnAbilityGranted);
	}
	
	
	
	// Display effect messages on a viewport
	OmegaAbilitySystemComponent->OnEffectAssetTagsUpdatedDelegate.AddLambda([this](const FGameplayTagContainer& InAssetTags, const FGameplayEffectSpec& AppliedEffectSpec)
	{
		for (const FGameplayTag& Tag : InAssetTags)
		{
			if (!Tag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Message")))) continue;

			// Message Data
			FUIWidgetRow* Row = UOmegaFunctionLibrary::GetDataTableRowByTag<FUIWidgetRow>(WidgetMessageDataTable, Tag);
			Row->EffectMagnitude = AppliedEffectSpec.GetModifierMagnitude(0.f, false);
			
			if (Row) { MessageWidgetRowDelegate.Broadcast(*Row);	}
			else { UE_LOG(LogTemp, Error, TEXT("[%hs]: Message widget row in %s doesn't exist!"), __FUNCTION__, *WidgetMessageDataTable->GetName()) } 
		}
	});
}

void UOverlayWidgetController::OnInitializeStartupAbilities(UOmegaAbilitySystemComponent* OmegaAbilitySystemComponent)
{
	if (!OmegaAbilitySystemComponent->bStartupAbilitiesGranted) return;

	FForEachAbility BroadcastDelegate;
	BroadcastDelegate.BindLambda([this, OmegaAbilitySystemComponent](const FGameplayAbilitySpec& InAbilitySpec)
	{
		checkf(AbilityInfo, TEXT("[%hs]: Ability info is null! Check for Overlay Widget controller defaults"), __FUNCTION__)
		
		FGameplayTag AbilityTag = OmegaAbilitySystemComponent->GetAbilityTagBySpec(InAbilitySpec);
		if (!AbilityTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities")))) return;
		
		FGameplayTag InputTag = OmegaAbilitySystemComponent->GetInputTagBySpec(InAbilitySpec);
		FOmegaAbilityInfo OmegaAbilityInfo = AbilityInfo->AbilityInfoMap[AbilityTag]; 
		
		OmegaAbilityInfo.InputTag = InputTag;
		
		
		OnAbilityInfoDelegate.Broadcast(OmegaAbilityInfo);
	});

	OmegaAbilitySystemComponent->ForEachAbility(BroadcastDelegate);
}

void UOverlayWidgetController::OnAbilityGranted(UOmegaAbilitySystemComponent* OmegaAbilitySystemComponent, const FGameplayAbilitySpec& InAbilitySpec)
{
	FGameplayTag AbilityTag = OmegaAbilitySystemComponent->GetAbilityTagBySpec(InAbilitySpec);
	if (!AbilityTag.MatchesTag(FGameplayTag::RequestGameplayTag(FName("Abilities")))) return;
	
	FOmegaAbilityInfo OmegaAbilityInfo = AbilityInfo->AbilityInfoMap[AbilityTag]; 
		
	OmegaAbilityInfo.InputTag = OmegaAbilitySystemComponent->GetInputTagBySpec(InAbilitySpec);
	OmegaAbilityInfo.CooldownTag = OmegaAbilitySystemComponent->GetAbilityTagBySpec(InAbilitySpec);
	
	OnAbilityInfoDelegate.Broadcast(OmegaAbilityInfo);
}
