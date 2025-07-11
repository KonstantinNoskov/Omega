#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "OmegaGameMode.generated.h"

class ULoadMenuSaveGame;
class USaveGame;
class UMVVM_LoadSlot;
class UDamageWidgetData;
class UCharacterDefaultInfo;

UCLASS()
class OMEGA_API AOmegaGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	
	static void DeleteSlot(const FString& SlotName, int32 SlotIndex);
	
	void SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex);
	ULoadMenuSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex);
	void TravelToMap(UMVVM_LoadSlot* LoadSlot);
	virtual AActor* ChoosePlayerStart_Implementation(AController* Player) override;
	ULoadMenuSaveGame* GetInGameSaveData();
	void SaveInGameProgressData(ULoadMenuSaveGame* SaveObject);

	

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Character Class Defaults")
	UCharacterDefaultInfo* CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|UI")
	UDamageWidgetData* DamageWidgetData;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> LoadMenuSaveGameClass;

	UPROPERTY(EditDefaultsOnly)
	FString StartingMapName;

	UPROPERTY(EditDefaultsOnly)
	FString DefaultMapName;
	
	UPROPERTY(EditDefaultsOnly)
	TSoftObjectPtr<UWorld> DefaultMap;
	
	UPROPERTY(EditDefaultsOnly)
	TMap<FString, TSoftObjectPtr<UWorld>> Maps;

	UPROPERTY(EditDefaultsOnly)
	FName DefaultPlayerStartTag;

protected:
	
	virtual void BeginPlay() override;
};
