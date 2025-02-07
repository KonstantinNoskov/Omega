#pragma once

#include "CoreMinimal.h"
#include "OmegaTypes.h"
#include "PaperCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "OmegaMovementComponent.generated.h"

class AOmegaCharacter;
enum class ECustomMovementMode : uint8;
struct FInputActionValue;

DECLARE_MULTICAST_DELEGATE(FOnDashStartSignature);

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

	TObjectPtr<AOmegaCharacter> OmegaOwner;

	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	ECustomMovementMode OmegaCustomMovementMode = ECustomMovementMode::None;
	
#pragma region JUMP

	UFUNCTION()
	void PerformJump(const FInputActionValue& InputActionValue) const;

	bool IsValidJump() const;

#pragma endregion

#pragma region CROUCH

	UFUNCTION()
	void PerformCrouch(const FInputActionValue& InputActionValue) const;

#pragma endregion

#pragma region DASH


	void HandleDash(const FInputActionValue& InputActionValue);
	void PerformDash();
	bool IsValidDash();

public:

	UFUNCTION(BlueprintPure)
	FORCEINLINE bool IsDashing() const { return bDashing; }

private:

	// Dash input flag
	UPROPERTY(BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	bool bDashing = false;
	
	float DashStarTime = 0.f;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = "true"), Category = "Omega Movement|Dash")
	float DashDuration = .2f;

	FTimerHandle DashTimer;
	
	void OnDashFinished();

protected:
	
	UPROPERTY(EditDefaultsOnly, Category = "Omega Movement|Dash")
	float DashImpulse = 1000.f;

	UPROPERTY(EditDefaultsOnly, Category = "Omega Movement|Dash")
	float DashCooldown = 1.f;

public:
	
	FOnDashStartSignature OnDashStartDelegate;

#pragma endregion

	
	
	
	
};
