#include "Player/OmegaPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Input/OmegaInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperCharacter.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


AOmegaPlayerController::AOmegaPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOmegaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AssignMappingContext();	
}

void AOmegaPlayerController::AssignMappingContext() const
{
	// Mapping context should be set
	check(InputMappingContext)
	
	UEnhancedInputLocalPlayerSubsystem* InputSubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());

	if (InputSubSystem)
	{
		// Set mapping context
		InputSubSystem->AddMappingContext(InputMappingContext, 0);
	}
}

void AOmegaPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// EnhancedInputComponent Valid Check
	UOmegaInputComponent* OmegaInputComponent = CastChecked<UOmegaInputComponent>(InputComponent);

	OmegaInputComponent->BindAction(MoveAction,	ETriggerEvent::Triggered, this, &AOmegaPlayerController::Move);
	OmegaInputComponent->BindAction(JumpAction,	ETriggerEvent::Started, this, &AOmegaPlayerController::Jump);
	OmegaInputComponent->BindAction(CrouchAction,	ETriggerEvent::Started, this, &AOmegaPlayerController::Crouch);
	OmegaInputComponent->BindAction(CrouchAction,	ETriggerEvent::Completed, this, &AOmegaPlayerController::Crouch);
	OmegaInputComponent->BindAction(DashAction,	ETriggerEvent::Started, this, &AOmegaPlayerController::Dash);
	OmegaInputComponent->BindAction(DashAction,	ETriggerEvent::Completed, this, &AOmegaPlayerController::Dash);

	OmegaInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagHeld, &ThisClass::AbilityInputTagReleased);
}

void AOmegaPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	//GEngine->AddOnScreenDebugMessage(1, 1.f, FColor::Green, *InputTag.ToString());
}

void AOmegaPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	GetOmegaAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
}

void AOmegaPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	GetOmegaAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
}

UOmegaAbilitySystemComponent* AOmegaPlayerController::GetOmegaAbilitySystemComponent()
{
	if (!OmegaAbilitySystemComponent)
	{
		OmegaAbilitySystemComponent = Cast<UOmegaAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	
	return OmegaAbilitySystemComponent;
}

void AOmegaPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const float InputFloat = InputActionValue.Get<float>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(FVector(InputFloat, 0.f,0.f));
		
		if (ControlledPawn->GetMovementComponent()->IsFalling()) return;
		
		// Rotate character sprite mesh towards to it's direction
		RotateController();
	}
}

void AOmegaPlayerController::RotateController()
{
	if (const ACharacter* PlayerCharacter = GetCharacter())
	{
		const FVector CurrentAcceleration = PlayerCharacter->GetCharacterMovement()->GetCurrentAcceleration();
		if (!CurrentAcceleration.X) return;
		
		const float YawRotation = CurrentAcceleration.X > 0.f ? 0.f : 180.f;
		SetControlRotation(FRotator(0.f,YawRotation,0.f));
	}
}

void AOmegaPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	OnJumpInputDelegate.Broadcast(InputActionValue);
}

void AOmegaPlayerController::Crouch(const FInputActionValue& InputActionValue)
{
	OnCrouchInputDelegate.Broadcast(InputActionValue);
}

void AOmegaPlayerController::Attack(const FInputActionInstance& InputActionInstance)
{
	
}

void AOmegaPlayerController::Dash(const FInputActionValue& InputActionValue)
{
	OnDashInputDelegate.Broadcast(InputActionValue);
}




