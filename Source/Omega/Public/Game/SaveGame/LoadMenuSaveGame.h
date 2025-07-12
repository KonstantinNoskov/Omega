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


USTRUCT(BlueprintType)
struct FSavedActorData
{
	GENERATED_BODY()

	UPROPERTY()
	FName ActorName = FName();

	UPROPERTY()
	FTransform Transform = FTransform();

	// Serialized variables from the Actor - only those marked with SaveGame specifier
	UPROPERTY()
	TArray<uint8> Bytes;
};

inline bool operator==(const FSavedActorData& Left, const FSavedActorData& Right)
{
	return Left.ActorName == Right.ActorName;
}

USTRUCT(BlueprintType)
struct FSavedMapData
{
	GENERATED_BODY()

	UPROPERTY()
	FString MapAssetName = FString();

	UPROPERTY()
	TArray<FSavedActorData> SavedActorsData;
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

	UPROPERTY()
	float Health = 0.f;

	UPROPERTY()
	float MaxHealth = 0.f;

	
	//  World State
	// ===============================================================================================================

	FSavedMapData GetSavedMapDataWithMapName(const FString& MapAssetName);

	bool HasMapData(const FString& MapAssetName);
	
	UPROPERTY()
	TArray<FSavedMapData> SavedMapsData;
};
