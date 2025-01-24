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
	
};
