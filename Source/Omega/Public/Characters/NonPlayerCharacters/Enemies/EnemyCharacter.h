#pragma once

#include "CoreMinimal.h"
#include "Characters/OmegaCharacter.h"
#include "Interfaces/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

class AOmegaAIController;
class UBehaviorTree;

UCLASS()
class OMEGA_API AEnemyCharacter : public AOmegaCharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter(const FObjectInitializer& ObjectInitializer);

	virtual void PossessedBy(AController* NewController) override;

protected:
	
	virtual void BeginPlay() override;
	

protected:
#pragma region COMBAT INTERFACE

public:
	
	FORCEINLINE virtual int32 GetPlayerLevel() const override { return Level; }

#pragma endregion
#pragma region AI

	UPROPERTY(EditAnywhere, Category = "AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

	UPROPERTY()
	TObjectPtr<AOmegaAIController> OmegaAIController;

#pragma endregion

protected:
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
