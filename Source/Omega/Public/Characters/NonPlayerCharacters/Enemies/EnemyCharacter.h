

#pragma once

#include "CoreMinimal.h"
#include "Characters/OmegaCharacter.h"
#include "EnemyCharacter.generated.h"

UCLASS()
class OMEGA_API AEnemyCharacter : public AOmegaCharacter
{
	GENERATED_BODY()

public:
	AEnemyCharacter();

protected:
	virtual void BeginPlay() override;

public:
	
};
