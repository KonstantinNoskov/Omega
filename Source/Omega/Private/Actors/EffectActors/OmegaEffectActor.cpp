#include "Actors/EffectActors/OmegaEffectActor.h"

#include "AbilitySystemInterface.h"
#include "PaperFlipbookComponent.h"
#include "AbilitySystem/OmegaAttributeSet.h"
#include "Components/SphereComponent.h"

AOmegaEffectActor::AOmegaEffectActor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Collision sphere is gonna be a root component
	InteractionSphere = CreateDefaultSubobject<USphereComponent>("Interaction Sphere");
	SetRootComponent(InteractionSphere);

	Mesh = CreateDefaultSubobject<UPaperFlipbookComponent>("Mesh");
	Mesh->SetupAttachment(GetRootComponent());
}

void AOmegaEffectActor::BeginPlay()
{
	Super::BeginPlay();

	InteractionSphere->OnComponentBeginOverlap.AddDynamic(this, &AOmegaEffectActor::OnInteractionSphereOverlap);
	InteractionSphere->OnComponentEndOverlap.AddDynamic(this, &AOmegaEffectActor::OnInteractionSphereEndOverlap);
}

void AOmegaEffectActor::OnInteractionSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if (IAbilitySystemInterface* ASCInterface = Cast<IAbilitySystemInterface>(OtherActor))
	{
		const UOmegaAttributeSet* OmegaAttributeSet = Cast<UOmegaAttributeSet>(ASCInterface->GetAbilitySystemComponent()->GetAttributeSet(UOmegaAttributeSet::StaticClass()));
		UOmegaAttributeSet* MutableAuraAttributeSet = const_cast<UOmegaAttributeSet*>(OmegaAttributeSet);
		MutableAuraAttributeSet->SetHealth(OmegaAttributeSet->GetHealth() + 5.f);
		Destroy();
	}
}

void AOmegaEffectActor::OnInteractionSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}

