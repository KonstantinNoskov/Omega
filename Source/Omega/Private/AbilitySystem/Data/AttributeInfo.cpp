#include "AbilitySystem/Data/AttributeInfo.h"

FOmegaAttributeInfo UAttributeInfo::FindAttributeInfoByTag(const FGameplayTag& AttributeTag, bool bLogNotFound)
{
	for (auto Attribute : PrimaryAttributesInfo)
	{	
		if (Attribute.Value.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Attribute.Value;
		}
	}
	
	for (auto Attribute : SecondaryAttributesInfo)
	{	
		if (Attribute.Value.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Attribute.Value;
		}
	}

	for (auto Attribute : TertiaryAttributesInfo)
	{	
		if (Attribute.Value.AttributeTag.MatchesTagExact(AttributeTag))
		{
			return Attribute.Value;
		}
	}
	
	if (bLogNotFound)
		{ UE_LOG(LogTemp, Error, TEXT("[%hs] GameplayTagInfo not found by Tag '[%s]'"), __FUNCTION__, *AttributeTag.ToString())	}

	return FOmegaAttributeInfo();
}
