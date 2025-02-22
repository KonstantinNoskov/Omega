#include "AbilitySystem/Abilities/OmegaProjectileAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Actors/OmegaProjectile.h"
#include "Interfaces/CombatInterface.h"


void UOmegaProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	FVector ProjectileSocketLocation;
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()) )
	{
		 ProjectileSocketLocation = CombatInterface->GetProjectileSpawnLocation();
	}

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(ProjectileSocketLocation);
	SpawnTransform.SetRotation(FRotator(0.f,GetAvatarActorFromActorInfo()->GetActorRotation().Yaw, 0.f).Quaternion());
	
	// Create and define projectile
	AOmegaProjectile* Projectile = GetWorld()->SpawnActorDeferred<AOmegaProjectile>(
		ProjectileClass,
		SpawnTransform,
		GetOwningActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn
		);

	if (!IsValid(Projectile))
	{
		UE_LOG(LogTemp, Error, TEXT("[%hs] Spawned projectile is null! Probably the projectile class in %s is not set."), __FUNCTION__, *this->GetName())
		return;
	}

	// TODO: Write a comment
	const UAbilitySystemComponent* SourceASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	const FGameplayEffectSpecHandle SpecHandle = SourceASC->MakeOutgoingSpec(DamageEffectClass, GetAbilityLevel(), SourceASC->MakeEffectContext());
	Projectile->DamageEffectSpecHandle = SpecHandle;
	
	// Finish spawning
	Projectile->FinishSpawning(SpawnTransform);
}
