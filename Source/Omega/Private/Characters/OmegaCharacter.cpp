#include "Characters/OmegaCharacter.h"

#include "PaperZDAnimationComponent.h"

AOmegaCharacter::AOmegaCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	PaperAnimation = CreateDefaultSubobject<UPaperZDAnimationComponent>("PaperZD Animation");
}

void AOmegaCharacter::BeginPlay()
{
	Super::BeginPlay();
}

