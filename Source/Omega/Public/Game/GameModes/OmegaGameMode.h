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

	void SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex);
	ULoadMenuSaveGame* GetSaveSlotData(const FString& SlotName, int32 SlotIndex);

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Character Class Defaults")
	UCharacterDefaultInfo* CharacterClassInfo;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|UI")
	UDamageWidgetData* DamageWidgetData;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<USaveGame> LoadMenuSaveGameClass;
};
