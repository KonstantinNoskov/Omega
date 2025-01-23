#include "Player/OmegaPlayerController.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "PaperCharacter.h"
#include "Characters/PlayerCharacters/RedHoodCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AOmegaPlayerController::AOmegaPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AOmegaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AssignMappingContext();	
}

void AOmegaPlayerController::AssignMappingContext()
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
	UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent);

	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &AOmegaPlayerController::Move);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Triggered, this, &AOmegaPlayerController::Jump);
	
}

void AOmegaPlayerController::Move(const FInputActionValue& InputActionValue)
{
	const float InputFloat = InputActionValue.Get<float>();

	if (APawn* ControlledPawn = GetPawn<APawn>())
	{
		ControlledPawn->AddMovementInput(FVector(InputFloat, 0.f,0.f));

		// Контроллер нельзя развернуть в воздухе
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
	if (APaperCharacter* PlayerCharacter = Cast<APaperCharacter>(GetCharacter()))
	{
		PlayerCharacter->Jump();
	}
}




