#include "Characters/NonPlayerCharacters/Enemies/EnemyCharacter.h"

#include "OmegaCollisionChannels.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "AbilitySystem/OmegaAttributeSet.h"
#include "AI/OmegaAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/CapsuleComponent.h"


AEnemyCharacter::AEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	
	PrimaryActorTick.bCanEverTick = false;

	AbilitySystemComponent = CreateDefaultSubobject<UOmegaAbilitySystemComponent>("Omega Ability System");
	AttributeSet = CreateDefaultSubobject<UOmegaAttributeSet>("Omega Attribute Set");

#pragma region COLLISION CHANNELS

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Enemy);

#pragma endregion
}

void AEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	OmegaAIController = Cast<AOmegaAIController>(NewController);
	OmegaAIController->GetBlackboardComponent()->InitializeBlackboard(*BehaviorTree->BlackboardAsset);
	OmegaAIController->RunBehaviorTree(BehaviorTree);
	
}


void AEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(AbilitySystemComponent))
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	else { UE_LOG(LogTemp, Error, TEXT("[%hs]: Ability System is null!"), __FUNCTION__); }
	
}

void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UOmegaAbilitySystemComponent* OmegaASC = Cast<UOmegaAbilitySystemComponent>(AbilitySystemComponent);
	if (OmegaASC)
	{
		OmegaASC->OnAbilityActorInfoSet();
	}
}



