#include "UI/MVVM/MVVM_LoadMenu.h"

#include "UI/MVVM/MVVM_LoadSlot.h"

void UMVVM_LoadMenu::InitializeLoadSlots()
{
	MVVM_LoadSlot_0 = NewObject<UMVVM_LoadSlot>(this, MVVM_LoadSlotClass);
	LoadSlots.Add(0, MVVM_LoadSlot_0);
	
	MVVM_LoadSlot_1 = NewObject<UMVVM_LoadSlot>(this, MVVM_LoadSlotClass);
	LoadSlots.Add(1, MVVM_LoadSlot_1);
	
	MVVM_LoadSlot_2 = NewObject<UMVVM_LoadSlot>(this, MVVM_LoadSlotClass);
	LoadSlots.Add(2, MVVM_LoadSlot_2);
}

UMVVM_LoadSlot* UMVVM_LoadMenu::GetLoadSlotViewModelByIndex(int32 Index)
{
	return LoadSlots.FindChecked(Index);
}

void UMVVM_LoadMenu::NewSlotButtonPressed(int32 SlotIndex, const FString& EnteredName)
{
	
}

void UMVVM_LoadMenu::NewGameButtonPressed(int32 SlotIndex)
{
	LoadSlots[SlotIndex]->SetWidgetSwitcherIndex.Broadcast(1);
}

void UMVVM_LoadMenu::SelectSlotButtonPressed(int32 SlotIndex)
{
	
}
