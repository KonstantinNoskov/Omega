#include "UI/ViewModel/MVVM_LoadMenu.h"

#include "UI/ViewModel/MVVM_LoadSlot.h"

void UMVVM_LoadMenu::InitializeLoadSlots()
{
	// Create Load Slots
	LoadSlot_0 =  NewObject<UMVVM_LoadSlot>(this, MVVM_LoadSlotClass);
	LoadSlots.Add(0, LoadSlot_0);
	
	LoadSlot_1 =  NewObject<UMVVM_LoadSlot>(this, MVVM_LoadSlotClass);
	LoadSlots.Add(1, LoadSlot_1);
	
	LoadSlot_2 =  NewObject<UMVVM_LoadSlot>(this, MVVM_LoadSlotClass);
	LoadSlots.Add(2, LoadSlot_2);
}

UMVVM_LoadSlot* UMVVM_LoadMenu::GetLoadSlotViewModelByIndex(int32 Index) const
{
	return LoadSlots.FindChecked(Index);
}
