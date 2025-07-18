#include "Input/InputData.h"

UTexture2D* UInputData::GetInputIconByTag(const FGameplayTag Tag)
{
	for (auto InputData : InputDataList)
	{
		if (InputData.Key.MatchesTagExact(Tag))
		{
			return InputData.Value.InputIcon;
		}
	}
	
	return nullptr; 
}
