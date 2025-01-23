#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OmegaPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

UCLASS()
class OMEGA_API AOmegaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AOmegaPlayerController();
	
protected:
	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void AssignMappingContext();

private:
	
	void Move(const FInputActionValue& InputActionValue);
		
	void Jump(const FInputActionValue& InputActionValue);

	void RotateController();

	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputAction> JumpAction;
};
