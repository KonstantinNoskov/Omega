#include "Components/OmegaMovementComponent.h"

#include "InputActionValue.h"
#include "OmegaCollisionChannels.h"
#include "PaperCharacter.h"
#include "Characters/OmegaCharacter.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/OmegaPlayerController.h"

UOmegaMovementComponent::UOmegaMovementComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	NavAgentProps.bCanCrouch = true;
}

void UOmegaMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OmegaOwner = Cast<AOmegaCharacter>(GetOwner());
}

void UOmegaMovementComponent::BindToPlayerController(AController* OwningController)
{
	if (AOmegaPlayerController* PlayerController = Cast<AOmegaPlayerController>(OwningController))
	{
		PlayerController->OnJumpInputDelegate.AddUObject(this, &UOmegaMovementComponent::PerformJump);
		PlayerController->OnCrouchInputDelegate.AddUObject(this, &UOmegaMovementComponent::PerformCrouch);
		PlayerController->OnDashInputDelegate.AddUObject(this, &UOmegaMovementComponent::HandleDash);
	}
}

void UOmegaMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

#pragma region JUMP

void UOmegaMovementComponent::PerformJump(const FInputActionValue& InputActionValue) const
{
	const float InputBool = InputActionValue.Get<bool>();
	
	if (OmegaOwner)
	{	
		if (InputBool && IsValidJump())
		{
			OmegaOwner->Jump();
		}
	}
}
bool UOmegaMovementComponent::IsValidJump() const 
{
	const bool bNotValid =
		!OmegaOwner
	||	IsCrouching();

	if(bNotValid) return false;
	
	bool bJumpValid;

	FHitResult HitResult;
	const UWorld* World = GetWorld();
	const float CapsuleHalfHeight = OmegaOwner->GetCapsuleComponent()->GetScaledCapsuleHalfHeight() * .5f;
	const FVector TraceStart = OmegaOwner->GetCapsuleComponent()->GetComponentLocation() + FVector(0.f,0.,CapsuleHalfHeight) * 2;
	const FVector TraceEnd = TraceStart + FVector(0.f,0.f, 10.f);
	const float CapsuleRadius = OmegaOwner->GetCapsuleComponent()->GetScaledCapsuleRadius();

	UKismetSystemLibrary::CapsuleTraceSingle(
		World,
		TraceStart,
		TraceEnd,
		CapsuleRadius,
		CapsuleHalfHeight,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		TArray<AActor*>(), EDrawDebugTrace::ForDuration, HitResult, true);

	bJumpValid = !HitResult.bBlockingHit; 

	return bJumpValid;
}

#pragma endregion

#pragma region CROUCH

void UOmegaMovementComponent::PerformCrouch(const FInputActionValue& InputActionValue) const
{
	const float InputBool = InputActionValue.Get<bool>();
	
	if (OmegaOwner)
	{
		if (InputBool && !IsFalling() )
		{
			OmegaOwner->Crouch();
		}
		else
		{
			OmegaOwner->UnCrouch();
		}
	}
}

#pragma endregion

#pragma region DASH

void UOmegaMovementComponent::HandleDash(const FInputActionValue& InputActionValue)
{
	if (IsValidDash())
	{
		PerformDash();
	}
}

bool UOmegaMovementComponent::IsValidDash()
{
	
	const float CurrentTime = GetWorld()->GetTimeSeconds();
	if (CurrentTime - DashStarTime >= DashCooldown)
	{
		return IsWalking() && !IsCrouching();
	}
	
	return false;
}

void UOmegaMovementComponent::OnDashFinished()
{
	bDashing = false;
	OmegaOwner->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Enemy, ECR_Overlap);
}

void UOmegaMovementComponent::PerformDash()
{
	bDashing = true;
	DashStarTime = GetWorld()->GetTimeSeconds();
	
	const FVector DashDirection = (Acceleration.IsNearlyZero() ? OmegaOwner->GetActorForwardVector() : Acceleration).GetSafeNormal2D();
	
	//Velocity = (Acceleration.Length() < 100.f ? DashImpulse * DashDirection: Velocity);
	Velocity =  DashImpulse * DashDirection;
	
	const FQuat NewRotation = FRotationMatrix::MakeFromXZ(DashDirection, FVector::UpVector).ToQuat();
	
	FHitResult HitResult;
	SafeMoveUpdatedComponent(FVector::ZeroVector, NewRotation, false, HitResult);

	OmegaOwner->GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Enemy, ECR_Ignore);
	
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindUObject(this, &UOmegaMovementComponent::OnDashFinished);
		
	GetWorld()->GetTimerManager().SetTimer(DashTimer, TimerDelegate, DashDuration, false);
}

#pragma endregion






