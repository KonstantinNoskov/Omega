#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "InputAction.h"
#include "InputActionValue.h"
#include "GameFramework/PlayerController.h"
#include "OmegaPlayerController.generated.h"

class UOmegaInputConfig;
class UInputAction;
class UInputMappingContext;


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
	void Attack(const FInputActionInstance& InputActionInstance);


#pragma region DASH

private:
	
	void Dash(const FInputActionValue& InputActionValue);

public:
	
	FOnInputRecievedSignature OnDashInputDelegate;

#pragma endregion

private:

	void RotateController();

	void AbilityInputTagPressed(FGameplayTag InputTag);
	void AbilityInputTagHeld(FGameplayTag InputTag);
	void AbilityInputTagReleased(FGameplayTag InputTag);
	

	UPROPERTY(EditDefaultsOnly, Category = "Input")
	TObjectPtr<UOmegaInputConfig> InputConfig;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputMappingContext> InputMappingContext;
	
	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> MoveAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> JumpAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> CrouchAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> DashAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> PrimaryAttackAction;

	UPROPERTY(EditAnywhere, Category = "Input")
	TObjectPtr<UInputAction> SecondaryAttackAction;

public:
	
	FOnInputRecievedSignature OnJumpInputDelegate;
	FOnInputRecievedSignature OnCrouchInputDelegate;
	FOnInputRecievedSignature OnMoveInputDelegate;
	
};
