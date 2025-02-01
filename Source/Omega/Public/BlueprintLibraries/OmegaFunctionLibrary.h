#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "OmegaFunctionLibrary.generated.h"

struct FGameplayTag;
class UPaperSprite;

UCLASS()
class OMEGA_API UOmegaFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	template <typename T>
	static T* GetDataTableRowByTag(UDataTable* InDataTable, const FGameplayTag& InTag)
	{
		return InDataTable->FindRow<T>(InTag.GetTagName(), TEXT(""));
	}

	UFUNCTION(BlueprintPure, meta = (DisplayName = "Get Source Size", Keywords = "Source Texture Sprite"), Category = "Omega|StaticFunctions")
	static FVector2D GetSourceSize(UPaperSprite* Sprite);
	
};
