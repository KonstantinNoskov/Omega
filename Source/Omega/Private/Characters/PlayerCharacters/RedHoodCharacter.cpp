#include "Characters/PlayerCharacters/RedHoodCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

ARedHoodCharacter::ARedHoodCharacter()
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

void ARedHoodCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

void ARedHoodCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	HandleCameraBehavior(DeltaSeconds);
}


void ARedHoodCharacter::HandleCameraBehavior(const float DeltaTime) const
{	
	const float CurrentCameraDistance = CharacterSpringArm->TargetArmLength;
	const float CurrentVelocity = GetCharacterMovement()->GetLastUpdateVelocity().Length();
	const float TargetCameraDistance = CurrentCameraDistance * (CurrentVelocity / 100);

	const float InterpCameraDistance = FMath::FInterpTo(CurrentCameraDistance, TargetCameraDistance, DeltaTime, CameraDistanceUpdateSpeed);
	const float ClampCameraDistance = FMath::Clamp(InterpCameraDistance, InitialCameraDistance, MaxCameraDistance);
	
	CharacterSpringArm->TargetArmLength = ClampCameraDistance;
}

