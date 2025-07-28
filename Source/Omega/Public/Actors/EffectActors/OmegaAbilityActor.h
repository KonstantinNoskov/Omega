#pragma once

#include "CoreMinimal.h"
#include "Actors/PickupActor.h"
#include "GameFramework/Actor.h"
#include "OmegaAbilityActor.generated.h"

class UOmegaGameplayAbility;
class UAbilitySystemComponent;
class UWidgetComponent;
class UBoxComponent;
class UGameplayAbility;



UCLASS()
class OMEGA_API AOmegaAbilityActor : public APickupActor
{
	GENERATED_BODY()

public:
	
	AOmegaAbilityActor();

protected:
	
	virtual void BeginPlay() override;

public:
	
	
	virtual void Tick(float DeltaTime) override;

	
	void GrantAbility(AActor* AbilityReciever);

protected:
	virtual void OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
		const FHitResult& SweepResult) override;

	
	UPROPERTY(EditAnywhere, Category = "Omega")
	TSubclassOf<UOmegaGameplayAbility> AbilityClass;
	

	UPROPERTY(VisibleAnywhere, Category = "Omega", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> WidgetComponent; 
};


