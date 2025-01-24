#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "OmegaAbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OMEGA_API UOmegaAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:

	UOmegaAbilitySystemComponent();

protected:

	virtual void BeginPlay() override;

public:

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
};
