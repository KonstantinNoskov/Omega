#include "Actors/PickupActor.h"

#include "OmegaCollisionChannels.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetMathLibrary.h"


APickupActor::APickupActor()
{
	
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxCollision->SetupAttachment(GetRootComponent());
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
    BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
    BoxCollision->SetCollisionResponseToChannel(ECC_Player, ECR_Overlap);
    BoxCollision->SetBoxExtent(FVector(30.f,10.f,32.f));
}


void APickupActor::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &APickupActor::OnCollisionOverlap);
}


void APickupActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HoveringActor(DeltaTime);
}

void APickupActor::HoveringActor(float DeltaTime)
{
	Radians = Radians > 360.f ? 0.f : (Radians + DeltaTime) + HoverMagnitude;

	float HoverSin = UKismetMathLibrary::Sin(Radians) * HoverAmplitude;

	FVector Offset = FVector(0.f,0.f,HoverSin);   
	BoxCollision->AddWorldOffset(Offset);
}

void APickupActor::OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                      const FHitResult& SweepResult)
{

	UGameplayStatics::PlaySoundAtLocation(this, PickupSound, GetActorLocation());
	Destroy();
}

