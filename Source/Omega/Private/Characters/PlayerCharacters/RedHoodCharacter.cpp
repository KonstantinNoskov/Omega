#include "Characters/PlayerCharacters/RedHoodCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"

ARedHoodCharacter::ARedHoodCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	CharacterSpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	CharacterSpringArm->SetupAttachment(GetRootComponent());

	CharacterCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	CharacterCamera->SetupAttachment(CharacterSpringArm);
}

void ARedHoodCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

