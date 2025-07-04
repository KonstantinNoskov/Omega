#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "Game/SaveGame/LoadMenuSaveGame.h"
#include "MVVM_LoadSlot.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FSetWidgetSwitcherIndex, int32, WidgetSwitcherIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FEnableSelectSlotButton, bool, bEnable);

UCLASS()
class OMEGA_API UMVVM_LoadSlot : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:
	
	void InitializeSlot();
	
	UPROPERTY(BlueprintAssignable)
	FSetWidgetSwitcherIndex SetWidgetSwitcherIndex;

	UPROPERTY(BlueprintAssignable)
	FEnableSelectSlotButton EnableSelectSlotButton;

	/*UPROPERTY()
	FString PlayerName;
	

	UPROPERTY()
	FString LoadSlotName;

	UPROPERTY()
	FString SlotIndex;
	*/	

	// Player Name
	FText GetPlayerName() const								{ return PlayerName; }
	void SetPlayerName(const FText& NewPlayerName)			{ UE_MVVM_SET_PROPERTY_VALUE(PlayerName, NewPlayerName); }

	// Load Slot Name
	FString GetLoadSlotName() const							{ return LoadSlotName; }
	void SetLoadSlotName(const FString& NewLoadSlotName)	{ UE_MVVM_SET_PROPERTY_VALUE(LoadSlotName, NewLoadSlotName); }

	// Slot Index
	int32 GetSlotIndex() const								{ return SlotIndex; }
	void SetSlotIndex(int32 NewSlotIndex)					{ UE_MVVM_SET_PROPERTY_VALUE(SlotIndex, NewSlotIndex); }


	UPROPERTY()
	TEnumAsByte<ESaveSlotStatus> SlotStatus;

private:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
	FText PlayerName = FText::FromString("Unknown Hero");

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
	FString LoadSlotName{"LoadSlot_00"};

	UPROPERTY(EditAnywhere, BlueprintReadWrite, FieldNotify, Setter, Getter, meta = (AllowPrivateAccess = "true"))
	int32 SlotIndex;
	
};
