#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "PaperCharacter.h"
#include "PaperFlipbookComponent.h"
#include "Interfaces/CombatInterface.h"

#include "OmegaCharacter.generated.h"

class UGameplayAbility;
class UOmegaMovementComponent;
class UGameplayEffect;
class UAttributeSet;
class UAbilitySystemComponent;
class UPaperZDAnimationComponent;

UCLASS()
class OMEGA_API AOmegaCharacter : public APaperCharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:

	AOmegaCharacter(const FObjectInitializer& ObjectInitializer);

protected:

	virtual void BeginPlay() override;

public:

	FORCEINLINE virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override		{ return AbilitySystemComponent; }
	FORCEINLINE UAttributeSet* GetAttributeSet() const											{ return AttributeSet; }
	virtual UPawnMovementComponent* GetMovementComponent() const override;

protected:
	
	/**
	 * Assign owner & avatar actor to Ability system 
	 */
	virtual void InitAbilityActorInfo();

private:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "PaperZD", meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UPaperZDAnimationComponent> PaperAnimation;

	
protected:

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

public:
	
	virtual bool ProcessConsoleExec(const TCHAR* Cmd, FOutputDevice& Ar, UObject* Executor) override;
	
	// -------------------------------------
	//  ATTRIBUTES
	// -------------------------------------

protected:
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
	
	void InitializeDefaultAttributes(const TSubclassOf<UGameplayEffect>& DefaultAttributesEffect, float Level) const;
	
	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default Attributes", DisplayName = "Primary Attributes")
	TSubclassOf<UGameplayEffect> DefaultPrimaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default Attributes", DisplayName = "Secondary Attributes")
	TSubclassOf<UGameplayEffect> DefaultSecondaryAttributes;

	UPROPERTY(BlueprintReadOnly, EditAnywhere, Category = "Default Attributes", DisplayName = "Tertiary Attributes")
	TSubclassOf<UGameplayEffect> DefaultTertiaryAttributes;

	// -------------------------------------
	//  MOVEMENT
	// -------------------------------------
	
public:
	
	virtual void PossessedBy(AController* NewController) override;

protected:
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"), Category = "Omega Movement")
	TObjectPtr<UOmegaMovementComponent> OmegaMovementComponent;

	// -------------------------------------
	//  ABILITIES
	// -------------------------------------

protected:

	void AddCharacterAbilities();

public:
	
	virtual FVector GetProjectileSpawnLocation() override;

protected:
	
	UPROPERTY(EditAnywhere, Category = "Omega|Combat")
	FName ProjectileSpawnSocket;
	
private:
	
	UPROPERTY(EditAnywhere, Category = "Omega|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;


	
};
