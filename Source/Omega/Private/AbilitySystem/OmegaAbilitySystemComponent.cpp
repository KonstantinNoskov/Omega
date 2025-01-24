#include "AbilitySystem/OmegaAbilitySystemComponent.h"


UOmegaAbilitySystemComponent::UOmegaAbilitySystemComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UOmegaAbilitySystemComponent::BeginPlay()
{
	Super::BeginPlay();
}


void UOmegaAbilitySystemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

