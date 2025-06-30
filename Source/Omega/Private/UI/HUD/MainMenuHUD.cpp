#include "UI/HUD/MainMenuHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/MVVM/MVVM_LoadMenu.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	// Create Load Menu View Model
	MVVM_LoadMenu = NewObject<UMVVM_LoadMenu>(this, MVVM_LoadMenuClass);
	MVVM_LoadMenu->InitializeLoadSlots();

	MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuWidgetClass);
	MainMenuWidget->AddToViewport();
}
