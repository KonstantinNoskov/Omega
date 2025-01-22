#pragma once

#include "CoreMinimal.h"
#include "Characters/OmegaCharacter.h"
#include "RedHoodCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class OMEGA_API ARedHoodCharacter : public AOmegaCharacter
{
	GENERATED_BODY()

public:

	ARedHoodCharacter();

protected:

	virtual void BeginPlay() override;

private:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CharacterSpringArm;

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CharacterCamera;
	
};
