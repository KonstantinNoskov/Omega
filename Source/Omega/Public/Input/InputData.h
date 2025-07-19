#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "InputData.generated.h"

class UPaperSprite;

USTRUCT(BlueprintType, Blueprintable)
struct FInputInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UTexture2D> InputIcon = nullptr; 
};

UCLASS()
class OMEGA_API UInputData : public UDataAsset
{
	GENERATED_BODY()

public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(ForceInlineRow));
	TMap<FGameplayTag, FInputInfo> InputDataList;
	
	UFUNCTION(BlueprintPure)
	UTexture2D* GetInputIconByTag(const FGameplayTag Tag);
};
