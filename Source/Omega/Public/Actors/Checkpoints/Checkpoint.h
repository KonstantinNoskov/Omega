#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerStart.h"
#include "Checkpoint.generated.h"

class UBoxComponent;
class UOmegaWidgetComponent;
class UPaperFlipbookComponent;

UCLASS()
class OMEGA_API ACheckpoint : public APlayerStart
{
	GENERATED_BODY()

public:

	ACheckpoint(const FObjectInitializer& ObjectInitializer);

	UFUNCTION()
	void OnCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	virtual void BeginPlay() override;

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
