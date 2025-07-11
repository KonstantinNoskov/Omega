#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "LoadMenuSaveGame.generated.h"

UENUM(BlueprintType)
enum ESaveSlotStatus
{
	Vacant,
	EnterName,
	Taken
};

UCLASS()
class OMEGA_API ULoadMenuSaveGame : public USaveGame
{
	GENERATED_BODY()

public:

	UPROPERTY()
	FString SlotName = FString();

	UPROPERTY()
	int32 SlotIndex = 0;

	UPROPERTY()
	FText PlayerName = FText::FromString("Default Name");

	UPROPERTY()
	FText MapName = FText::FromString("Default Map");

	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SaveSlotStatus = Vacant;

	UPROPERTY()
	FName PlayerStartTag;

	UPROPERTY()
	bool bFirstTimeLoadIn = true;


	//  Player Attribute Data
	// ===============================================================================================================

	UPROPERTY()
	float Strength = 0.f;

	UPROPERTY()
	float Dexterity = 0.f;

	UPROPERTY()
	float Intelligence = 0.f;
};
