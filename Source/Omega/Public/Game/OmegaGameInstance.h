#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "OmegaGameInstance.generated.h"

UCLASS()
class OMEGA_API UOmegaGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	
	UPROPERTY()
	FName PlayerStartTag = FName();

	UPROPERTY()
	FString LoadSlotName = FString();

	UPROPERTY()
	int32 LoadSlotIndex = 0;
};
