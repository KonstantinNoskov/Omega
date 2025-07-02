#include "UI/MVVM/MVVM_LoadMenu.h"

#include "Game/GameModes/OmegaGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "UI/MVVM/MVVM_LoadSlot.h"

void UMVVM_LoadMenu::InitializeLoadSlots()
{
	MVVM_LoadSlot_0 = NewObject<UMVVM_LoadSlot>(this, MVVM_LoadSlotClass);
	MVVM_LoadSlot_0->SetLoadSlotName("LoadSlot_0");
	LoadSlots.Add(0, MVVM_LoadSlot_0);
	
	MVVM_LoadSlot_1 = NewObject<UMVVM_LoadSlot>(this, MVVM_LoadSlotClass);
	MVVM_LoadSlot_1->SetLoadSlotName("LoadSlot_1");
	LoadSlots.Add(1, MVVM_LoadSlot_1);
	
	MVVM_LoadSlot_2 = NewObject<UMVVM_LoadSlot>(this, MVVM_LoadSlotClass);
	MVVM_LoadSlot_2->SetLoadSlotName("LoadSlot_2");
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
	
	//LoadSlots[SlotIndex]->SetPlayerName(EnteredName);
	LoadSlots[SlotIndex]->SlotStatus = Taken;
	
	OmegaGameMode->SaveSlotData(LoadSlots[SlotIndex], SlotIndex);
	LoadSlots[SlotIndex]->InitializeSlot();
	
}

void UMVVM_LoadMenu::NewGameButtonPressed(int32 SlotIndex)
{
	LoadSlots[SlotIndex]->SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadMenu::SelectSlotButtonPressed(int32 SlotIndex)
{
	
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
		LoadSlot.Value->InitializeSlot();
	}
}
