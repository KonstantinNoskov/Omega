#pragma once

#include "CoreMinimal.h"
#include "MVVMViewModelBase.h"
#include "MVVM_LoadMenu.generated.h"

class UMVVM_LoadSlot;

UCLASS()
class OMEGA_API UMVVM_LoadMenu : public UMVVMViewModelBase
{
	GENERATED_BODY()

public:

	void InitializeLoadSlots();

	UFUNCTION(BlueprintPure)
	UMVVM_LoadSlot* GetLoadSlotViewModelByIndex(int32 Index);
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadSlot> MVVM_LoadSlotClass;

private:

	UPROPERTY()
	TMap<int32, UMVVM_LoadSlot*> LoadSlots;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> MVVM_LoadSlot_0;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> MVVM_LoadSlot_1;

	UPROPERTY()
	TObjectPtr<UMVVM_LoadSlot> MVVM_LoadSlot_2;
};
