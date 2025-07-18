#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "OmegaAbilityActor.generated.h"

class UOmegaGameplayAbility;
class UAbilitySystemComponent;
class UWidgetComponent;
class UBoxComponent;
class UGameplayAbility;

UCLASS()
class OMEGA_API AOmegaAbilityActor : public AActor
{
	GENERATED_BODY()

public:
	
	AOmegaAbilityActor();

protected:
	
	virtual void BeginPlay() override;

public:
	
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	void HoveringActor(float DeltaTime);
	void GrantAbility(AActor* AbilityReciever);

	UFUNCTION()
	void OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:

	UPROPERTY(EditAnywhere, Category = "Omega")
	TSubclassOf<UOmegaGameplayAbility> AbilityClass;

	UPROPERTY(EditAnywhere, Category = "Omega")
	int32 AbilityLevel{1};

	UPROPERTY(EditAnywhere, Category = "Omega")
	float HoverAmplitude{.5f};

	UPROPERTY(EditAnywhere, Category = "Omega")
	float HoverMagnitude{.025f};

private:

	float Radians{0.f};
	
	UPROPERTY(VisibleAnywhere, Category = "Omega", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UBoxComponent> BoxCollision;

	UPROPERTY(VisibleAnywhere, Category = "Omega", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UWidgetComponent> WidgetComponent; 
};


