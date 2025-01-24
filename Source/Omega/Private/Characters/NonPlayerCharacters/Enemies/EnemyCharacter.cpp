#include "Characters/NonPlayerCharacters/Enemies/EnemyCharacter.h"

#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "AbilitySystem/OmegaAttributeSet.h"


AEnemyCharacter::AEnemyCharacter()
{
	
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UOmegaAbilitySystemComponent>("Omega Ability System");
	AttributeSet = CreateDefaultSubobject<UOmegaAttributeSet>("Omega Attribute Set");
}


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	checkf(AbilitySystemComponent, TEXT("[%hs]: Ability System is null!"), __FUNCTION__)
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
}



