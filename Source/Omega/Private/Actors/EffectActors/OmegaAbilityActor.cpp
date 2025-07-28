#include "Actors/EffectActors/OmegaAbilityActor.h"

#include "GameplayAbilitySpec.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/OmegaGameplayAbility.h"
#include "AbilitySystem/Data/AbilityInfo.h"
#include "Characters/PlayerCharacters/PlayerBaseCharacter.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"

AOmegaAbilityActor::AOmegaAbilityActor()
{
	PrimaryActorTick.bCanEverTick = true;
	
	WidgetComponent = CreateDefaultSubobject<UWidgetComponent>("Widget Component");
	WidgetComponent->SetupAttachment(BoxCollision);
	WidgetComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WidgetComponent->SetRelativeRotation(FRotator(0, 90.f, 0));
}

void AOmegaAbilityActor::BeginPlay()
{
	Super::BeginPlay();
	
}

void AOmegaAbilityActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
}



void AOmegaAbilityActor::OnCollisionOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)	
{
	if (!OtherActor->Implements<UAbilitySystemInterface>()) return;
	GrantAbility(OtherActor);
	
	Super::OnCollisionOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
}



void AOmegaAbilityActor::GrantAbility(AActor* AbilityReceiver)
{
	APlayerBaseCharacter* Player = Cast<APlayerBaseCharacter>(AbilityReceiver);
	if (!Player) return;
	UOmegaAbilitySystemComponent* PlayerASC = Cast<UOmegaAbilitySystemComponent>(Player->GetAbilitySystemComponent());
	if (!PlayerASC) return;
	if (!AbilityClass) return;

	FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, AbilityLevel);
	AbilitySpec.DynamicAbilityTags.AddTag(AbilityClass.GetDefaultObject()->StartupInputTag);

	PlayerASC->GiveAbility(AbilitySpec);
	PlayerASC->OnAbilityGrantedDelegate.Broadcast(PlayerASC);
	//PlayerASC->OnAbilityGrantedBySpecDelegate.Broadcast(PlayerASC, AbilitySpec);
}


