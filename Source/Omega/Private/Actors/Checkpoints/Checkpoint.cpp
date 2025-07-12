#include "Actors/Checkpoints/Checkpoint.h"

#include "OmegaCollisionChannels.h"
#include "PaperFlipbookComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "Game/GameModes/OmegaGameMode.h"
#include "Interfaces/PlayerInterface.h"
#include "Kismet/BlueprintTypeConversions.h"
#include "Kismet/GameplayStatics.h"
#include "UI/WidgetComponents/OmegaWidgetComponent.h"

ACheckpoint::ACheckpoint(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	
	OverlapBox = CreateDefaultSubobject<UBoxComponent>("Overlap Box");
	OverlapBox->SetupAttachment(GetRootComponent());
	OverlapBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	OverlapBox->SetCollisionResponseToAllChannels(ECR_Ignore);
	OverlapBox->SetCollisionResponseToChannel(ECC_Player, ECR_Overlap);

	FlipbookComponent = CreateDefaultSubobject<UPaperFlipbookComponent>("Flipbook Component");
	FlipbookComponent->SetupAttachment(OverlapBox);
}


void ACheckpoint::BeginPlay()
{
	Super::BeginPlay();

	OverlapBox->OnComponentBeginOverlap.AddDynamic(this, &ThisClass::OnCheckpointOverlap);
}

void ACheckpoint::OnCheckpointOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (bReached) return;

	bReached = true;
	
	// Save Player Data
	if (!OtherActor->Implements<UPlayerInterface>()) return;
	IPlayerInterface::Execute_SaveProgress(OtherActor, PlayerStartTag);

	// Save World Data
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(this));
	if (IsValid(OmegaGameMode)) 
	{
		OmegaGameMode->SaveWorldState(GetWorld());
	}
	
	// Show Save notify widget
	if (IsValid(SavedGameWidgetComponentClass))
	{
		UOmegaWidgetComponent* SaveGameWidget = NewObject<UOmegaWidgetComponent>(this, SavedGameWidgetComponentClass);
		SaveGameWidget->AttachToComponent(GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		SaveGameWidget->RegisterComponent();
		SaveGameWidget->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);

		OverlapBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	}
	else
	{
		UE_LOG(LogClass, Warning, TEXT("[%hs]: Checkpoint widget component class is not set. Check for Checkpoint default settings."), __FUNCTION__)
	}

	// Play Save Sound
	UGameplayStatics::PlaySoundAtLocation(this, SavedSound, GetActorLocation());
}