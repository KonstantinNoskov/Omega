#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"

#include "OmegaCharacter.generated.h"

class UPaperFlipbook;

UCLASS()
class OMEGA_API AOmegaCharacter : public APaperCharacter
{
	GENERATED_BODY()

public:

	AOmegaCharacter();

protected:

	virtual void BeginPlay() override;
	
	
};
