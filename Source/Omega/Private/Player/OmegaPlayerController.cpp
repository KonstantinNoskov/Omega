﻿#include "Player/OmegaPlayerController.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "Input/OmegaInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "OmegaGameplayTags.h"
#include "PaperCharacter.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "Characters/OmegaCharacter.h"
#include "Components/OmegaMovementComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "UI/Widgets/DamageTextComponent.h"


AOmegaPlayerController::AOmegaPlayerController()
{
	PrimaryActorTick.bCanEverTick = true;
	
}

void AOmegaPlayerController::BeginPlay()
{
	Super::BeginPlay();

	AssignMappingContext();
	SetActorHiddenInGame(false);
}


//  SETUP
// -------------------------------------

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

	
	UOmegaInputComponent* OmegaInputComponent = Cast<UOmegaInputComponent>(InputComponent);
	if (!OmegaInputComponent) return;

	OmegaInputComponent->BindAction(MoveAction,		ETriggerEvent::Triggered, this, &AOmegaPlayerController::Move);
	OmegaInputComponent->BindAction(JumpAction,		ETriggerEvent::Started, this, &AOmegaPlayerController::Jump);
	OmegaInputComponent->BindAction(CrouchAction,	ETriggerEvent::Triggered, this, &AOmegaPlayerController::Crouch);
	OmegaInputComponent->BindAction(CrouchAction,	ETriggerEvent::Completed, this, &AOmegaPlayerController::Crouch);
	OmegaInputComponent->BindAction(DashAction,		ETriggerEvent::Started, this, &AOmegaPlayerController::Dash);
	OmegaInputComponent->BindAction(DashAction,		ETriggerEvent::Completed, this, &AOmegaPlayerController::Dash);

	OmegaInputComponent->BindAbilityActions(InputConfig, this, &ThisClass::AbilityInputTagPressed, &ThisClass::AbilityInputTagHeld, &ThisClass::AbilityInputTagReleased);
}


//  INPUT
// ==========================================

void AOmegaPlayerController::AbilityInputTagPressed(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FOmegaGameplayTags::Get().InputTag_Mouse_LMB))
	{
		GetOmegaAbilitySystemComponent()->AbilityInputTagPressed(InputTag);
	}

	FGameplayTag AbilityTag = FOmegaGameplayTags::Get().InputTag_Mouse_RMB;
	
	if (InputTag.MatchesTagExact(FOmegaGameplayTags::Get().InputTag_Mouse_RMB))
	{
		GetOmegaAbilitySystemComponent()->AbilityInputTagPressed(InputTag);
	}
}
void AOmegaPlayerController::AbilityInputTagHeld(FGameplayTag InputTag)
{
	if (InputTag.MatchesTagExact(FOmegaGameplayTags::Get().InputTag_Mouse_LMB))
	{
		if (GetOmegaAbilitySystemComponent())
		{
			GetOmegaAbilitySystemComponent()->AbilityInputTagHeld(InputTag);
		}
	}

	ElapsedPressTime += GetWorld()->GetDeltaSeconds();
	
}
void AOmegaPlayerController::AbilityInputTagReleased(FGameplayTag InputTag)
{
	if (!GetOmegaAbilitySystemComponent()) return;
	GetOmegaAbilitySystemComponent()->AbilityInputTagReleased(InputTag);
}


//  COMMON FUNCTIONS
// -------------------------------------

UOmegaAbilitySystemComponent* AOmegaPlayerController::GetOmegaAbilitySystemComponent()
{
	if (!OmegaAbilitySystemComponent)
	{
		OmegaAbilitySystemComponent = Cast<UOmegaAbilitySystemComponent>(UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetPawn<APawn>()));
	}
	
	return OmegaAbilitySystemComponent;
}
UOmegaMovementComponent* AOmegaPlayerController::GetOmegaMovementComponent()
{
	if (!OmegaMovementComponent)
	{
		OmegaMovementComponent = Cast<UOmegaMovementComponent>(GetPawn<APawn>()->GetMovementComponent());
	}
	
	return OmegaMovementComponent;
}
void AOmegaPlayerController::Move(const FInputActionValue& InputActionValue)
{	
	const float InputFloat = InputActionValue.Get<float>();

	if (AOmegaCharacter* ControlledPawn = Cast<AOmegaCharacter>(GetPawn<APawn>()))
	{
		bool bMoveable = GetOmegaMovementComponent()->GetOmegaCustomMovementMode() == EOmegaCustomMovementMode::NONE;
		
		if (GetOmegaMovementComponent()->GetOmegaCustomMovementMode() != EOmegaCustomMovementMode::NONE) return;
		
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


//  CUSTOM MOVEMENT
// -------------------------------------

// Jump
void AOmegaPlayerController::Jump(const FInputActionValue& InputActionValue)
{
	if (GetOmegaMovementComponent())
	{
		GetOmegaMovementComponent()->PerformJump(InputActionValue);
	}
}

// Crouch
void AOmegaPlayerController::Crouch(const FInputActionValue& InputActionValue)
{
	if (GetOmegaMovementComponent())
	{
		OmegaMovementComponent->HandleCrouch(InputActionValue);
	}
}

// Dash
void AOmegaPlayerController::Dash(const FInputActionValue& InputActionValue)
{
	if (GetOmegaMovementComponent())
	{
		GetOmegaMovementComponent()->HandleDash(InputActionValue);
	}
}
void AOmegaPlayerController::ShowFloatingText(const FDamageEffectContextData& DamageHandle, ACharacter* TargetCharacter)
{
	if (IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		// Create Damage widget, attach it to a damaged character
		// and detach it right away so the damage widget can float in the world space
		UDamageTextComponent* DamageText = NewObject<UDamageTextComponent>(this, DamageTextComponentClass);
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageText->RegisterComponent();
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		
		
		UE_LOG(LogTemp, Warning, TEXT("[%hs] %s "), __FUNCTION__, *TargetCharacter->GetRootComponent()->GetName());
		
		// Set Damage value
		DamageText->SetDamageText(DamageHandle);
	}
}




