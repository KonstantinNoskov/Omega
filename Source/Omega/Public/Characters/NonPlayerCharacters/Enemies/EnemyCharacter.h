#pragma once

#include "CoreMinimal.h"
#include "Characters/OmegaCharacter.h"
#include "Interfaces/EnemyInterface.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class OMEGA_API AEnemyCharacter : public AOmegaCharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	
	virtual void BeginPlay() override;

#pragma region COMBAT INTERFACE

public:
	
	FORCEINLINE virtual int32 GetPlayerLevel() const override { return Level; }

#pragma endregion

protected:
	virtual void InitAbilityActorInfo() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Character Class Defaults")
	int32 Level = 1;
};
