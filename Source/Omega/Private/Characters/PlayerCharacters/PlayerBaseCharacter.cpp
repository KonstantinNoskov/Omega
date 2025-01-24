#include "Characters/PlayerCharacters/PlayerBaseCharacter.h"

#include "AbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Player/OmegaPlayerState.h"

APlayerBaseCharacter::APlayerBaseCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	
	CharacterSpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	CharacterSpringArm->SetupAttachment(GetRootComponent());
	CharacterSpringArm->SetWorldRotation(FRotator(0.f,-90.f,0.f));
	CharacterSpringArm->TargetArmLength = 600.f;
	CharacterSpringArm->bInheritPitch = false;
	CharacterSpringArm->bInheritYaw = false;
	CharacterSpringArm->bInheritRoll = false;
	InitialCameraDistance = CharacterSpringArm->TargetArmLength;
	CharacterSpringArm->bEnableCameraLag = true;

	CharacterCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	CharacterCamera->SetupAttachment(CharacterSpringArm);
}

void APlayerBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void APlayerBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	HandleCameraBehavior(DeltaSeconds);
}

void APlayerBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitAbilityActorInfo();
}

void APlayerBaseCharacter::InitAbilityActorInfo()
{
	// Init ability actor info with player state valid check
	AOmegaPlayerState* OmegaPlayerState = GetPlayerState<AOmegaPlayerState>();
	checkf(OmegaPlayerState, TEXT("[%hs]: OmegaPlayerState for PlayerBaseCharacter is null!"), __FUNCTION__)
	OmegaPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(OmegaPlayerState, this);

	// Assign ability system  
	AbilitySystemComponent = OmegaPlayerState->GetAbilitySystemComponent();

	// Assign attribute set
	AttributeSet = OmegaPlayerState->GetAttributeSet();	
}


void APlayerBaseCharacter::HandleCameraBehavior(const float DeltaTime) const
{
	
	const float CurrentCameraDistance = CharacterSpringArm->TargetArmLength;
	const float CurrentVelocity = GetCharacterMovement()->GetLastUpdateVelocity().Length();
	const float TargetCameraDistance = CurrentCameraDistance * (CurrentVelocity / 100);

	const float InterpCameraDistance = FMath::FInterpTo(CurrentCameraDistance, TargetCameraDistance, DeltaTime, CameraDistanceUpdateSpeed);
	const float ClampCameraDistance = FMath::Clamp(InterpCameraDistance, InitialCameraDistance, MaxCameraDistance);
	
	CharacterSpringArm->TargetArmLength = ClampCameraDistance;
}



