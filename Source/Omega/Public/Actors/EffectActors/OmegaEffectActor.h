#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OmegaEffectActor.generated.h"

class UPaperFlipbookComponent;
class USphereComponent;

UCLASS()
class OMEGA_API AOmegaEffectActor : public AActor
{
	GENERATED_BODY()

public:
	
	AOmegaEffectActor();

protected:

	virtual void BeginPlay() override;


public:

	UFUNCTION()
	virtual void OnInteractionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void OnInteractionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> InteractionSphere;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UPaperFlipbookComponent> Mesh;
};
