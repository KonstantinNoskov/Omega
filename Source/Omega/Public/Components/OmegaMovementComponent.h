#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OmegaMovementComponent.generated.h"


struct FInputActionValue;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class OMEGA_API UOmegaMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:

	UOmegaMovementComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

protected:

	virtual void BeginPlay() override;

public:
	
	void BindToPlayerController(AController* OwningController);


private:

	UFUNCTION()
	void MyJump(const FInputActionValue& InputActionValue);

	UFUNCTION()
	void MyCrouch(const FInputActionValue& InputActionValue);


};
