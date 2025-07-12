#include "Game/GameModes/OmegaGameMode.h"

#include "EngineUtils.h"
#include "NiagaraCommon.h"
#include "Game/OmegaGameInstance.h"
#include "Game/SaveGame/LoadMenuSaveGame.h"
#include "GameFramework/PlayerStart.h"
#include "Interfaces/SaveInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Serialization/ObjectAndNameAsStringProxyArchive.h"
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
	LoadMenuSaveGame->PlayerStartTag = LoadSlot->PlayerStartTag;
	
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

AActor* AOmegaGameMode::ChoosePlayerStart_Implementation(AController* Player)
{
	UOmegaGameInstance* OmegaGameInstance = Cast<UOmegaGameInstance>(GetGameInstance());
	
	TArray<AActor*> Actors;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), APlayerStart::StaticClass(), Actors);
	if (Actors.Num() > 0)
	{
		AActor* SelectedActor = Actors[0];
		for (AActor* Actor : Actors)
		{
			if (APlayerStart* PlayerStart = Cast<APlayerStart>(Actor))
			{
				if (PlayerStart->PlayerStartTag == OmegaGameInstance->PlayerStartTag)
				{
					SelectedActor = PlayerStart;
					break;
				}
			}
		}
		
		return SelectedActor;
	}

	return nullptr;
}

ULoadMenuSaveGame* AOmegaGameMode::GetInGameSaveData()
{
	UOmegaGameInstance* OmegaGameInstance = Cast<UOmegaGameInstance>(GetGameInstance());

	const FString InGameLoadSlotName = OmegaGameInstance->LoadSlotName;
	const int32 InGameLoadSlotIndex = OmegaGameInstance->LoadSlotIndex;
	
	return GetSaveSlotData(InGameLoadSlotName, InGameLoadSlotIndex); 
}

void AOmegaGameMode::SaveInGameProgressData(ULoadMenuSaveGame* SaveObject)
{
	UOmegaGameInstance* OmegaGameInstance = Cast<UOmegaGameInstance>(GetGameInstance());

	const FString InGameLoadSlotName = OmegaGameInstance->LoadSlotName;
	const int32 InGameLoadSlotIndex = OmegaGameInstance->LoadSlotIndex;
	OmegaGameInstance->PlayerStartTag = SaveObject->PlayerStartTag;

	UGameplayStatics::SaveGameToSlot(SaveObject, InGameLoadSlotName, InGameLoadSlotIndex);
}

void AOmegaGameMode::SaveWorldState(UWorld* World)
{
	// Get World's name
	FString WorldName =  World->GetMapName();
	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);

	UOmegaGameInstance* OmegaGameInstance = Cast<UOmegaGameInstance>(GetGameInstance());
	check(OmegaGameInstance)

	if (ULoadMenuSaveGame* SaveGame = GetSaveSlotData(OmegaGameInstance->LoadSlotName, OmegaGameInstance->LoadSlotIndex))
	{
		// Save Map if it doesn't exist yet
		if (!SaveGame->HasMapData(WorldName))
		{
			FSavedMapData NewSavedMapData;
			NewSavedMapData.MapAssetName = WorldName;
			SaveGame->SavedMapsData.Add(NewSavedMapData);
		}

		// Get Current Map Data
		FSavedMapData SavedMapData = SaveGame->GetSavedMapDataWithMapName(WorldName);

		// ... and clear data of all actors in this map 
		SavedMapData.SavedActorsData.Empty(); // Clear saved actor list
		
		for (FActorIterator It(World); It; ++It)
		{
			AActor* Actor = *It;
			if (!IsValid(Actor) || !Actor->Implements<USaveInterface>()) continue;

			// Actor Saved Data
			FSavedActorData SavedActorData;
			SavedActorData.ActorName = Actor->GetFName();
			SavedActorData.Transform = Actor->GetTransform();

			// Archive
			FMemoryWriter MemoryWriter(SavedActorData.Bytes);
			FObjectAndNameAsStringProxyArchive Archive(MemoryWriter, true);
			Archive.ArIsSaveGame = true;

			Actor->Serialize(Archive);
			SavedMapData.SavedActorsData.AddUnique(SavedActorData);
		}

		for (FSavedMapData& MapDataToReplace : SaveGame->SavedMapsData)
		{
			if (MapDataToReplace.MapAssetName == WorldName)
			{
				MapDataToReplace = SavedMapData;
			}
		}

		UGameplayStatics::SaveGameToSlot(SaveGame,OmegaGameInstance->LoadSlotName, OmegaGameInstance->LoadSlotIndex);
	}
}

void AOmegaGameMode::LoadWorldState(UWorld* World) const
{
	FString WorldName =  World->GetMapName();
	WorldName.RemoveFromStart(World->StreamingLevelsPrefix);

	UOmegaGameInstance* OmegaGameInstance = Cast<UOmegaGameInstance>(GetGameInstance());
	check(OmegaGameInstance)

	if (UGameplayStatics::DoesSaveGameExist(OmegaGameInstance->LoadSlotName, OmegaGameInstance->LoadSlotIndex))
	{
		ULoadMenuSaveGame* SaveGame = Cast<ULoadMenuSaveGame>(UGameplayStatics::LoadGameFromSlot(OmegaGameInstance->LoadSlotName, OmegaGameInstance->LoadSlotIndex));
		if (!IsValid(SaveGame)) return;
		
		for (FActorIterator It(World); It; ++It)
		{
			AActor* Actor = *It;
			if (!IsValid(Actor) || !Actor->Implements<USaveInterface>()) continue;

			for (FSavedActorData SavedActorData : SaveGame->GetSavedMapDataWithMapName(WorldName).SavedActorsData)
			{
				if (SavedActorData.ActorName == Actor->GetFName())
				{
					UE_LOG(LogClass, Warning, TEXT("%s"), *Actor->GetFName().ToString())
					if (ISaveInterface::Execute_ShouldLoadTransform(Actor))
					{
						Actor->SetActorTransform(SavedActorData.Transform);
					}

					FMemoryReader MemoryReader(SavedActorData.Bytes);
					FObjectAndNameAsStringProxyArchive Archive(MemoryReader, true);
					Archive.ArIsSaveGame = true;
					Actor->Serialize(Archive);

					ISaveInterface::Execute_LoadActor(Actor);
				}
			}
		}
	}
}
