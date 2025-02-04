#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "OmegaPlayerController.generated.h"

class UInputAction;
class UInputMappingContext;
struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE_OneParam(FOnInputRecievedSignature, const FInputActionValue& Input)

UCLASS()
class OMEGA_API AOmegaPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	AOmegaPlayerController();
	
protected:
	
	virtual void BeginPlay() override;

	virtual void SetupInputComponent() override;

	void AssignMappingContext() const;

	

private:
	
	void Move(const FInputActionValue& InputActionValue);
		
	void Jump(const FInputActionValue& InputActionValue);

	void Crouch(const FInputActionValue& InputActionValue);

	void RotateController();

	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "input")
	TObjectPtr<UInputAction> CrouchAction;

public:
	
	FOnInputRecievedSignature OnJumpInputDelegate;
	FOnInputRecievedSignature OnCrouchInputDelegate;
};
