#include "Actors/EffectActors/OmegaAbilityActor.h"

#include "AbilitySystemInterface.h"
#include "GameplayAbilitySpec.h"
#include "OmegaCollisionChannels.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/OmegaGameplayAbility.h"
#include "Characters/PlayerCharacters/PlayerBaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Kismet/KismetMathLibrary.h"

AOmegaAbilityActor::AOmegaAbilityActor()
{
	PrimaryActorTick.bCanEverTick = true;

	BoxCollision = CreateDefaultSubobject<UBoxComponent>("Box Collision");
	BoxCollision->SetupAttachment(GetRootComponent());
	BoxCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	BoxCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BoxCollision->SetCollisionResponseToChannel(ECC_Player, ECR_Overlap);
	BoxCollision->SetBoxExtent(FVector(30.f,10.f,32.f));
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	WidgetComponent->SetupAttachment(BoxCollision);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WidgetComponent->SetRelativeRotation(FRotator(0, 90.f, 0));
}

void AOmegaAbilityActor::BeginPlay()
{
	Super::BeginPlay();

	BoxCollision->OnComponentBeginOverlap.AddDynamic(this, &AOmegaAbilityActor::OnCollisionOverlap);
}

void AOmegaAbilityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	HoveringActor(DeltaTime);
}

void AOmegaAbilityActor::HoveringActor(float DeltaTime)
{
	Radians = Radians > 360.f ? 0.f : (Radians + DeltaTime) + HoverMagnitude;

	float HoverSin = UKismetMathLibrary::Sin(Radians) * HoverAmplitude;

	FVector Offset = FVector(0.f,0.f,HoverSin);   
	BoxCollision->AddWorldOffset(Offset);
}



void AOmegaAbilityActor::OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                                            const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>() || !OtherActor->Implements<UAbilitySystemInterface>()) return;

	// Assign ability
	GrantAbility(OtherActor);

	Destroy();
}

void AOmegaAbilityActor::GrantAbility(AActor* AbilityOwner)
{
	APlayerBaseCharacter* Player = Cast<APlayerBaseCharacter>(AbilityOwner);
	if (!Player) return;
	UAbilitySystemComponent* PlayerASC = Player->GetAbilitySystemComponent();

	if (!AbilityClass) return;
	
 	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, AbilityLevel);
	AbilitySpec.DynamicAbilityTags.AddTag(AbilityClass.GetDefaultObject()->StartupInputTag);
	
	PlayerASC->GiveAbility(AbilitySpec);
}

