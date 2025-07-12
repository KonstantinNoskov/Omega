#pragma once

#include "CoreMinimal.h"
#include "Game/OmegaGameInstance.h"
#include "GameFramework/PlayerStart.h"
#include "Interfaces/SaveInterface.h"
#include "Checkpoint.generated.h"

class UBoxComponent;
class UOmegaWidgetComponent;
class UPaperFlipbookComponent;

UCLASS()
class OMEGA_API ACheckpoint : public APlayerStart, public ISaveInterface
{
	GENERATED_BODY()

public:

	ACheckpoint(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginPlay() override;

public:
	
	UFUNCTION()
	void OnCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	virtual bool ShouldLoadTransform_Implementation() override { return false; }
	//virtual void LoadActor_Implementation() override;

	UPROPERTY(BlueprintReadOnly, SaveGame)
	bool bReached = false;

private:

	UPROPERTY(VisibleAnywhere, Category = "Omega")
	TObjectPtr<UPaperFlipbookComponent> FlipbookComponent;

	UPROPERTY(VisibleAnywhere, Category = "Omega")
	TObjectPtr<UBoxComponent> OverlapBox;

	UPROPERTY(EditDefaultsOnly, Category = "Omega")
	TSubclassOf<UOmegaWidgetComponent> SavedGameWidgetComponentClass;
	
	UPROPERTY(EditDefaultsOnly)
	USoundBase* SavedSound;
};
