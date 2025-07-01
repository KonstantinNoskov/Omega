#include "Game/GameModes/OmegaGameMode.h"

#include "Game/SaveGame/LoadMenuSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MVVM/MVVM_LoadSlot.h"

void AOmegaGameMode::SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(LoadSlot->LoadSlotName, SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(LoadSlot->LoadSlotName, SlotIndex);
	}
	
	USaveGame* SaveGameObject =  UGameplayStatics::CreateSaveGameObject(LoadMenuSaveGameClass);
	ULoadMenuSaveGame* LoadMenuSaveGame = Cast<ULoadMenuSaveGame>(SaveGameObject);
	LoadMenuSaveGame->PlayerName = LoadSlot->PlayerName;

	UGameplayStatics::SaveGameToSlot(LoadMenuSaveGame, LoadSlot->LoadSlotName, SlotIndex);
}
