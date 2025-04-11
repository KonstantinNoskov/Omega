#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "MMC_Health.generated.h"


UCLASS()
class OMEGA_API UMMC_Health : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()

public:

	UMMC_Health();

	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;

	private:
	
};
