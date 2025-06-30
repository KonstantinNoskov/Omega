#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UMVVM_LoadMenu;

UCLASS()
class OMEGA_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuWidgetClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UUserWidget> MainMenuWidget;


	//  LOAD MENU
	// ===============================================================================================================

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadMenu> MVVM_LoadMenuClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMVVM_LoadMenu> MVVM_LoadMenu;
 

protected:
	
	virtual void BeginPlay() override;
};
