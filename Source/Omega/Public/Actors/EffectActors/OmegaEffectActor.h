﻿#pragma once

#include "CoreMinimal.h"
#include "OmegaTypes.h"
#include "ScalableFloat.h"
#include "GameFramework/Actor.h"
#include "OmegaEffectActor.generated.h"

/*
 * Used to handle gameplay effect apply conditions
 */
UENUM(BlueprintType)
enum class EEffectApplicationPolicy : uint8
{
	ApplyOnOverlap,
	ApplyOnEndOverlap,
	DoNotApply
};

/*
 * Used to handle gameplay effect removal conditions
 */
UENUM(BlueprintType)
enum class EEffectRemovalPolicy : uint8
{
	RemoveOnOverlap,
	RemoveOnEndOverlap,
	DoNotRemove
};

struct FActiveGameplayEffectHandle;

class UGameplayEffect;
class UPaperFlipbookComponent;

UCLASS()
class OMEGA_API AOmegaEffectActor : public AActor
{
	GENERATED_BODY()

public:
	
	AOmegaEffectActor();

protected:

	virtual void BeginPlay() override;
	
	UFUNCTION(BlueprintCallable)
	void ApplyEffectToTarget(AActor* TargetActor, const TSubclassOf<UGameplayEffect>& InGameplayEffectClass, const EEffectApplicationPolicy& ApplyPolicy);

	UFUNCTION(BlueprintCallable)
	void OnOverlap(AActor* TargetActor);

	UFUNCTION(BlueprintCallable)
	void OnEndOverlap(AActor* TargetActor);

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Applied Effects")
	float ActorLevel = 1.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Omega|Applied Effects|Applied/Removal Policies|Instant Effect")
	TSubclassOf<UGameplayEffect> InstantGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Omega|Applied Effects|Applied/Removal Policies|Instant Effect")
	EEffectApplicationPolicy InstantEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Omega|Applied Effects|Applied/Removal Policies|Duration Effect")
	TSubclassOf<UGameplayEffect> DurationGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Omega|Applied Effects|Applied/Removal Policies|Duration Effect")
	EEffectApplicationPolicy DurationEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Omega|Applied Effects|Applied/Removal Policies|Duration Effect")
	EEffectRemovalPolicy DurationEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Omega|Applied Effects|Applied/Removal Policies|Infinite Effect")
	TSubclassOf<UGameplayEffect> InfiniteGameplayEffectClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Omega|Applied Effects|Applied/Removal Policies|Infinite Effect")
	EEffectApplicationPolicy InfiniteEffectApplicationPolicy = EEffectApplicationPolicy::DoNotApply;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Omega|Applied Effects|Applied/Removal Policies|Infinite Effect")
	EEffectRemovalPolicy InfiniteEffectRemovalPolicy = EEffectRemovalPolicy::RemoveOnEndOverlap;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Omega|Applied Effects")
	bool bDestroyOnEffectRemoval = false;
	
	UPROPERTY(EditDefaultsOnly, Category = "Omega|Applied Effects|Applied/Removal Policies|Instant Effect", meta=(ForceInlineRow))
	TMap<FGameplayTag, FScalableFloat> InstantDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Applied Effects|Applied/Removal Policies|Duration Effect", meta=(ForceInlineRow))
	TMap<FGameplayTag, FScalableFloat> DurationDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Omega|Applied Effects|Applied/Removal Policies|Infinite Effect", meta=(ForceInlineRow))
	TMap<FGameplayTag, FScalableFloat> InfiniteDamage;

	UPROPERTY(EditDefaultsOnly, Category = "Omega", meta=(ForceInlineRow))
	int32 EffectLevel = 1;

	TMap<EEffectApplicationPolicy, TMap<FGameplayTag, FScalableFloat>> DurationPolicyToDamage;
};
