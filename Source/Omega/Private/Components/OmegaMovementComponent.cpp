#include "Components/OmegaMovementComponent.h"

#include "InputActionValue.h"
#include "PaperCharacter.h"
#include "Player/OmegaPlayerController.h"

UOmegaMovementComponent::UOmegaMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	NavAgentProps.bCanCrouch = true;
}

void UOmegaMovementComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UOmegaMovementComponent::BindToPlayerController(AController* OwningController)
{
	if (AOmegaPlayerController* PlayerController = Cast<AOmegaPlayerController>(OwningController))
	{
		PlayerController->OnJumpInputDelegate.AddUObject(this, &UOmegaMovementComponent::MyJump);
		PlayerController->OnCrouchInputDelegate.AddUObject(this, &UOmegaMovementComponent::MyCrouch);
	}
}

void UOmegaMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
}


void UOmegaMovementComponent::MyJump(const FInputActionValue& InputActionValue)
{
	const float InputBool = InputActionValue.Get<bool>();
	
	if (APaperCharacter* PlayerCharacter = Cast<APaperCharacter>(GetCharacterOwner()) )
	{
		if (InputBool)
		{
			PlayerCharacter->Jump();	
		}
	}
}

void UOmegaMovementComponent::MyCrouch(const FInputActionValue& InputActionValue)
{
	const float InputBool = InputActionValue.Get<bool>();
	
	if (APaperCharacter* PlayerCharacter = Cast<APaperCharacter>(GetCharacterOwner()))
	{
		if (InputBool && !IsFalling() )
		{
			PlayerCharacter->Crouch();
		}
		else
		{
			PlayerCharacter->UnCrouch();
		}
	}
}

