#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OmegaProjectile.generated.h"

class UPaperFlipbookComponent;
class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class OMEGA_API AOmegaProjectile : public AActor
{
	GENERATED_BODY()

public:
	AOmegaProjectile();

protected:
	
	virtual void BeginPlay() override;

	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<USphereComponent> Sphere;
	
	UPROPERTY(Category = Character, VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperFlipbookComponent> Sprite;

public:

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement; 
};
