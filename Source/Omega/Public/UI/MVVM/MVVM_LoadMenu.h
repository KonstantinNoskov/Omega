#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadMenu.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE(FSlotSelected);

class UMVVM_LoadSlot;

UCLASS(BlueprintType, Blueprintable)
class OMEGA_API UMVVM_LoadMenu : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	void InitializeLoadSlots();

	UPROPERTY(BlueprintAssignable)
	FSlotSelected SlotSelected;

	UFUNCTION(BlueprintPure)
	UMVVM_LoadSlot* GetLoadSlotViewModelByIndex(int32 Index);

	UFUNCTION(BlueprintCallable)
	void NewSlotButtonPressed(int32 SlotIndex, const FString& EnteredName);

	UFUNCTION(BlueprintCallable)
	void NewGameButtonPressed(int32 SlotIndex);

	UFUNCTION(BlueprintCallable)
	void SelectSlotButtonPressed(int32 SlotIndex);

	void LoadData();

	UFUNCTION(BlueprintCallable)
	void DeleteButtonPressed();

	UFUNCTION(BlueprintCallable)
	void PlayButtonPressed();
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadSlot> MVVM_LoadSlotClass;

	// Slot Index
	int32 GetNumLoadSlots() const			{ return NumLoadSlots; }
	void SetNumLoadSlots(int32 NewSlotNum)	{ UE_MVVM_SET_PROPERTY_VALUE(NumLoadSlots, NewSlotNum); }

private:

	UPROPERTY()
	TMap<int32, UMVVM_LoadSlot*> LoadSlots;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> MVVM_LoadSlot_0;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> MVVM_LoadSlot_1;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> MVVM_LoadSlot_2;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> SelectedSlot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
	int32 NumLoadSlots;
};
