#include "UI/MVVM/MVVM_LoadMenu.h"

#include "Game/GameModes/OmegaGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetStringLibrary.h"
#include "UI/MVVM/MVVM_LoadSlot.h"

void UMVVM_LoadMenu::InitializeLoadSlots()
{
	MVVM_LoadSlot_0 = NewObject<UMVVM_LoadSlot>(this, MVVM_LoadSlotClass);
	MVVM_LoadSlot_0->SetLoadSlotName("LoadSlot_0");
	MVVM_LoadSlot_0->SetSlotIndex(0);
	LoadSlots.Add(0, MVVM_LoadSlot_0);
	
	MVVM_LoadSlot_1 = NewObject<UMVVM_LoadSlot>(this, MVVM_LoadSlotClass);
	MVVM_LoadSlot_1->SetLoadSlotName("LoadSlot_1");
	MVVM_LoadSlot_1->SetSlotIndex(1);
	LoadSlots.Add(1, MVVM_LoadSlot_1);
	
	MVVM_LoadSlot_2 = NewObject<UMVVM_LoadSlot>(this, MVVM_LoadSlotClass);
	MVVM_LoadSlot_2->SetLoadSlotName("LoadSlot_2");
	MVVM_LoadSlot_2->SetSlotIndex(2);
	LoadSlots.Add(2, MVVM_LoadSlot_2);

	SetNumLoadSlots(LoadSlots.Num());
}

UMVVM_LoadSlot* UMVVM_LoadMenu::GetLoadSlotViewModelByIndex(int32 Index)
{
	return LoadSlots.FindChecked(Index);
}

void UMVVM_LoadMenu::NewSlotButtonPressed(int32 SlotIndex, const FString& EnteredName)
{
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(this));
	FText MapName = FText::FromString(UKismetStringLibrary::GetSubstring(OmegaGameMode->DefaultMapName, 0, 8));
	
	LoadSlots[SlotIndex]->SetPlayerName(FText::FromString(EnteredName));
	LoadSlots[SlotIndex]->SetMapName(MapName);
	LoadSlots[SlotIndex]->SlotStatus = Taken;
	
	OmegaGameMode->SaveSlotData(LoadSlots[SlotIndex], SlotIndex);
	LoadSlots[SlotIndex]->InitializeSlot();
}

void UMVVM_LoadMenu::NewGameButtonPressed(int32 SlotIndex)
{
	for (auto LoadSlot : LoadSlots)
	{	
		if (LoadSlot.Key == SlotIndex)
		{
			LoadSlots[SlotIndex]->SetWidgetSwitcherIndex.Broadcast(1);		
		}
	}

	LoadSlots[SlotIndex]->SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadMenu::SelectSlotButtonPressed(int32 SlotIndex)
{
	SlotSelected.Broadcast();
	for (auto LoadSlot : LoadSlots)
	{
		if (LoadSlot.Key == SlotIndex)
		{
			LoadSlot.Value->EnableSelectSlotButton.Broadcast(false);		
		}
		else
		{
			LoadSlot.Value->EnableSelectSlotButton.Broadcast(true);	
		}
	}

	SelectedSlot = LoadSlots[SlotIndex];
}

void UMVVM_LoadMenu::DeleteButtonPressed()
{
	if (IsValid(SelectedSlot))
	{
		AOmegaGameMode::DeleteSlot(SelectedSlot->GetLoadSlotName(),  SelectedSlot->GetSlotIndex());
		SelectedSlot->SlotStatus = Vacant;
		SelectedSlot->InitializeSlot();
	}
	
	for (auto LoadSlot : LoadSlots)
	{
		LoadSlot.Value->EnableSelectSlotButton.Broadcast(true);
	}
}

void UMVVM_LoadMenu::PlayButtonPressed()
{
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(this));
	if (!IsValid(SelectedSlot)) return;
	OmegaGameMode->TravelToMap(SelectedSlot);
}


void UMVVM_LoadMenu::LoadData()
{
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(this));
	for (auto LoadSlot : LoadSlots)
	{
		ULoadMenuSaveGame* SaveObject = OmegaGameMode->GetSaveSlotData(LoadSlot.Value->GetLoadSlotName(), LoadSlot.Key);

		const FText PlayerName = SaveObject->PlayerName;
		LoadSlot.Value->SetPlayerName(PlayerName);
		LoadSlot.Value->SlotStatus = SaveObject->SaveSlotStatus;
		LoadSlot.Value->SetMapName(SaveObject->MapName);
		LoadSlot.Value->InitializeSlot();
	}
}

