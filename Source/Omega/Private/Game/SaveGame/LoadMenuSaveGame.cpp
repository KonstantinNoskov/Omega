#include "Game/SaveGame/LoadMenuSaveGame.h"

FSavedMapData ULoadMenuSaveGame::GetSavedMapDataWithMapName(const FString& MapAssetName)
{
	for (const FSavedMapData& SavedMapData : SavedMapsData)
	{
		if (SavedMapData.MapAssetName == MapAssetName)
		{
			return SavedMapData;
		}
	}
	
	return FSavedMapData(); 
}

bool ULoadMenuSaveGame::HasMapData(const FString& MapAssetName)
{
	for (const FSavedMapData& SavedMapData : SavedMapsData)
	{
		if (SavedMapData.MapAssetName == MapAssetName)
		{
			return true;
		}
	}
	
	return false;
}
