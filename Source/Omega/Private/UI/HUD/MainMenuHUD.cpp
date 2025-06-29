#include "UI/HUD/MainMenuHUD.h"

#include "Blueprint/UserWidget.h"
#include "UI/ViewModel/MVVM_LoadMenu.h"
#include "UI/Widgets/MainMenuOverlay.h"

void AMainMenuHUD::BeginPlay()
{
	Super::BeginPlay();

	// Main Menu
	MainMenuOverlay = CreateWidget<UMainMenuOverlay>(GetWorld(), MainMenuOverlayClass);
	if (!MainMenuOverlay) return;
	MainMenuOverlay->AddToViewport(0);
	 
	// Load Menu View Model
	MVVM_LoadMenu = NewObject<UMVVM_LoadMenu>(this, MVVM_LoadMenuClass);
	MVVM_LoadMenu->InitializeLoadSlots();
}
