#include "Game/GameModes/OmegaGameMode.h"

#include "Game/SaveGame/LoadMenuSaveGame.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MVVM/MVVM_LoadSlot.h"

void AOmegaGameMode::BeginPlay()
{
	Super::BeginPlay();

	Maps.Add(DefaultMapName, DefaultMap);
}

void AOmegaGameMode::SaveSlotData(UMVVM_LoadSlot* LoadSlot, int32 SlotIndex)
{
	DeleteSlot(LoadSlot->GetLoadSlotName(), LoadSlot->GetSlotIndex());	
	
	USaveGame* SaveGameObject =  UGameplayStatics::CreateSaveGameObject(LoadMenuSaveGameClass);
	ULoadMenuSaveGame* LoadMenuSaveGame = Cast<ULoadMenuSaveGame>(SaveGameObject);
	LoadMenuSaveGame->PlayerName = LoadSlot->GetPlayerName();
	LoadMenuSaveGame->MapName = LoadSlot->GetMapName();
	LoadMenuSaveGame->SaveSlotStatus = Taken;

	UGameplayStatics::SaveGameToSlot(LoadMenuSaveGame, LoadSlot->GetLoadSlotName(), SlotIndex);
}

void AOmegaGameMode::DeleteSlot(const FString& SlotName, int32 SlotIndex)
{
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
	{
		UGameplayStatics::DeleteGameInSlot(SlotName, SlotIndex);
	}
}

ULoadMenuSaveGame* AOmegaGameMode::GetSaveSlotData(const FString& SlotName, int32 SlotIndex)
{
	USaveGame* SaveGameObject = nullptr;
	if (UGameplayStatics::DoesSaveGameExist(SlotName, SlotIndex))
	{
		SaveGameObject = UGameplayStatics::LoadGameFromSlot(SlotName, SlotIndex);
	}
	else
	{
		SaveGameObject = UGameplayStatics::CreateSaveGameObject(LoadMenuSaveGameClass);
	}
	
	ULoadMenuSaveGame* LoadMenuSaveGame = Cast<ULoadMenuSaveGame>(SaveGameObject);
	return LoadMenuSaveGame;
}

void AOmegaGameMode::TravelToMap(UMVVM_LoadSlot* LoadSlot)
{
	const FString& SlotName = LoadSlot->GetLoadSlotName();
	const int32  SlotIndex = LoadSlot->GetSlotIndex();
	
	FString MapName = LoadSlot->GetMapName().ToString();
	TSoftObjectPtr<UWorld> MapToTravel = Maps.FindChecked(MapName);

	UGameplayStatics::OpenLevelBySoftObjectPtr(LoadSlot, MapToTravel);
}

