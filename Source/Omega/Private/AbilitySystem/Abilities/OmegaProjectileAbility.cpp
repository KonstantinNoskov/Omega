#include "AbilitySystem/Abilities/OmegaProjectileAbility.h"

#include "Abilities/Tasks/AbilityTask_WaitInputRelease.h"
#include "Actors/OmegaProjectile.h"
#include "Interfaces/CombatInterface.h"


void UOmegaProjectileAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                              const FGameplayEventData* TriggerEventData)
{
	
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	FVector ProjectileSocketLocation;
	if (ICombatInterface* CombatInterface = Cast<ICombatInterface>(GetAvatarActorFromActorInfo()) )
	{
		 ProjectileSocketLocation =CombatInterface->GetProjectileSpawnLocation();
	}

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(ProjectileSocketLocation);
	
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
	
	// Finish spawning
	Projectile->FinishSpawning(SpawnTransform);
}
