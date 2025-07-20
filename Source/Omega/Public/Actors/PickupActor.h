#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PickupActor.generated.h"

class UBoxComponent;

UCLASS()
class OMEGA_API APickupActor : public AActor
{
	GENERATED_BODY()

public:
	
	APickupActor();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void HoveringActor(float DeltaTime);

protected:

UFUNCTION()
	
	virtual void OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(EditAnywhere, Category = "Omega|Pickup", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USoundBase> PickupSound;



	UPROPERTY(EditAnywhere, Category = "Omega")
	int32 AbilityLevel{1};

	UPROPERTY(EditAnywhere, Category = "Omega")
	float HoverAmplitude{.5f};

	UPROPERTY(EditAnywhere, Category = "Omega")
	float HoverMagnitude{.025f};

private:

	float Radians{0.f};
	
};


