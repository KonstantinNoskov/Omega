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

	
	// -------------------------------------
	//  COLLISION CHANNELS
	// -------------------------------------

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Enemy);
	
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
	InitAbilityActorInfo();
	
}

#pragma region ENEMY INTERFACE

void AEnemyCharacter::SetCombatTarget_Implementation(AActor* TargetActor)
{
	if (!OmegaAIController)
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] OmegaAIController is null!"), __FUNCTION__)
		return;
	}
	
	UBlackboardComponent* Blackboard = OmegaAIController->GetBlackboardComponent();
	Blackboard->SetValueAsObject(CombatTargetName, TargetActor);
	
}

#pragma endregion


void AEnemyCharacter::InitAbilityActorInfo()
{
	AbilitySystemComponent->InitAbilityActorInfo(this, this);
	UOmegaAbilitySystemComponent* OmegaASC = Cast<UOmegaAbilitySystemComponent>(AbilitySystemComponent);
	if (OmegaASC)
	{
		OmegaASC->OnAbilityActorInfoSet();

		InitializeDefaultAttributes(DefaultPrimaryAttributes, 1.f);
		InitializeDefaultAttributes(DefaultSecondaryAttributes, 1.f);
		InitializeDefaultAttributes(DefaultTertiaryAttributes, 1.f);
	}
}



