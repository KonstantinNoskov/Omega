// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MainMenuHUD.generated.h"

class UMVVM_LoadMenu;
class UMainMenuOverlay;
/**
 * 
 */
UCLASS()
class OMEGA_API AMainMenuHUD : public AHUD
{
	GENERATED_BODY()

public:

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UUserWidget> MainMenuOverlayClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMainMenuOverlay> MainMenuOverlay;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UMVVM_LoadMenu> MVVM_LoadMenuClass;

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UMVVM_LoadMenu> MVVM_LoadMenu;
	
protected:
	
	virtual void BeginPlay() override;
	
};
