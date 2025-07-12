#include "Characters/PlayerCharacters/PlayerBaseCharacter.h"

#include "OmegaCollisionChannels.h"
#include "AbilitySystemComponent.h"
#include "AbilitySystem/OmegaAbilitySystemComponent.h"
#include "AbilitySystem/OmegaAttributeSet.h"
#include "BlueprintLibraries/OmegaFunctionLibrary.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/OmegaMovementComponent.h"
#include "Game/OmegaGameInstance.h"
#include "Game/GameModes/OmegaGameMode.h"
#include "Game/SaveGame/LoadMenuSaveGame.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Player/OmegaPlayerController.h"
#include "Player/OmegaPlayerState.h"
#include "UI/HUD/OmegaHUD.h"


void APlayerBaseCharacter::Landed(const FHitResult& Hit)
{
	Super::Landed(Hit);
}

APlayerBaseCharacter::APlayerBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = true;

	// =============================
	//  CAPSULE
	// =============================

	GetCapsuleComponent()->SetCapsuleHalfHeight(60.f);

	
	// -------------------------------------
	//  CAMERA
	// -------------------------------------
	
	CharacterSpringArm = CreateDefaultSubobject<USpringArmComponent>("Spring Arm");
	CharacterSpringArm->SetupAttachment(GetRootComponent());
	CharacterSpringArm->SetWorldRotation(FRotator(0.f,-90.f,0.f));
	CharacterSpringArm->TargetArmLength = 800.f;
	CharacterSpringArm->bInheritPitch = false;
	CharacterSpringArm->bInheritYaw = false;
	CharacterSpringArm->bInheritRoll = false;
	
	CharacterSpringArm->bEnableCameraLag = true;

	CharacterCamera = CreateDefaultSubobject<UCameraComponent>("Camera");
	CharacterCamera->SetupAttachment(CharacterSpringArm);
	CameraDistanceUpdateSpeed = .1f;
	
	
	// -------------------------------------
	//  COLLISION CHANNELS
	// -------------------------------------

	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Player);
	GetCapsuleComponent()->SetCollisionProfileName("Player");
	
}

void APlayerBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	InitialCameraDistance = CharacterSpringArm->TargetArmLength;
}

void APlayerBaseCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void APlayerBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	// Init GAS
	InitAbilityActorInfo();

	// Load Character Data
	LoadProgress();
	
	// Load Character Abilities
	AddCharacterAbilities();
	BindDependencies(NewController);
	
}

void APlayerBaseCharacter::BindDependencies(AController* NewController)
{

	// Bind new controller to a movement component
	if (OmegaMovementComponent)
	{
		OmegaMovementComponent->BindDependencies(NewController);
	}

	// On Capsule Hit
	GetCapsuleComponent()->OnComponentHit.AddDynamic(this, &APlayerBaseCharacter::OnCapsuleHit);
}
void APlayerBaseCharacter::OnCapsuleHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (OmegaMovementComponent)
	{
		OmegaMovementComponent->HandleHit();
	}
}

int32 APlayerBaseCharacter::GetPlayerLevel() const
{
	const AOmegaPlayerState* OmegaPlayerState = GetPlayerState<AOmegaPlayerState>();
	if (!OmegaPlayerState)
		{ UE_LOG(LogTemp, Error, TEXT("[%hs]: Can't get player level. PlayerState is null!"),__FUNCTION__)	return 0;	}

	return OmegaPlayerState->GetPlayerLevel();
}
void APlayerBaseCharacter::InitAbilityActorInfo()
{
	// Init ability actor info with player state valid check
	AOmegaPlayerState* OmegaPlayerState = GetPlayerState<AOmegaPlayerState>();
	if (!OmegaPlayerState)	{ UE_LOG(LogTemp, Error, TEXT("[%hs]: OmegaPlayerState for PlayerBaseCharacter is null!"),__FUNCTION__)		return;	}
	
	OmegaPlayerState->GetAbilitySystemComponent()->InitAbilityActorInfo(OmegaPlayerState, this);

	// Inform Ability system that all essential data is set and it's time to bind callbacks to ability system delegates (OnGameplayEffectApplied, etc.)
	UOmegaAbilitySystemComponent* OmegaASC = Cast<UOmegaAbilitySystemComponent>(OmegaPlayerState->GetAbilitySystemComponent());
	if (!OmegaASC)	{ UE_LOG(LogTemp, Error, TEXT("[%hs]: Cast from UAbilitySystem to UOmegaAbilitySystem is failed!"),__FUNCTION__)	return;	}
	
	OmegaASC->OnAbilityActorInfoSet();
	
	// Assign Player's Ability system & Attribute Set
	AbilitySystemComponent = OmegaPlayerState->GetAbilitySystemComponent();
	AttributeSet = OmegaPlayerState->GetAttributeSet();

	// Set player's default primary attributes 
	//InitializeDefaultAttributes(DefaultPrimaryAttributes,		1.f);
	//InitializeDefaultAttributes(DefaultSecondaryAttributes,	1.f);
	//InitializeDefaultAttributes(DefaultTertiaryAttributes,	1.f);

	//UOmegaFunctionLibrary::InitializeDefaultAttributes(this, OmegaASC);


	// Modify attributes depending on character tags 
	Super::InitAbilityActorInfo();

	if (AOmegaPlayerController* OmegaPlayerController = Cast<AOmegaPlayerController>(GetController()))
	{
		if (AOmegaHUD* OmegaHUD = Cast<AOmegaHUD>(OmegaPlayerController->GetHUD()))
		{
			OmegaHUD->InitOverlay(OmegaPlayerController, OmegaPlayerState, AbilitySystemComponent, AttributeSet);
		}
	}
}

void APlayerBaseCharacter::Die_Implementation()
{
	Super::Die_Implementation();
	if (APlayerController* PlayerController = Cast<APlayerController>(GetController()))
	{
		PlayerController->DisableInput(PlayerController);	
	}
}


void APlayerBaseCharacter::LoadProgress()
{
	// Game Mode Check
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(this));
	if (!IsValid(OmegaGameMode)) return;

	// Save Object Check
	ULoadMenuSaveGame* SaveData = OmegaGameMode->GetInGameSaveData();
	if (!SaveData) return;

	AOmegaPlayerState* OmegaPlayerState = GetPlayerState<AOmegaPlayerState>();
	if (!OmegaPlayerState)	{ UE_LOG(LogTemp, Error, TEXT("[%hs]: OmegaPlayerState for PlayerBaseCharacter is null!"),__FUNCTION__)		return;	}
	
		// Inform Ability system that all essential data is set and it's time to bind callbacks to ability system delegates (OnGameplayEffectApplied, etc.)
	UOmegaAbilitySystemComponent* OmegaASC = Cast<UOmegaAbilitySystemComponent>(OmegaPlayerState->GetAbilitySystemComponent());

	// Load Attribute Data
	UOmegaAttributeSet* OmegaAttributeSet = Cast<UOmegaAttributeSet>(GetAttributeSet());
	if (SaveData->bFirstTimeLoadIn)
	{	
		//InitializeDefaultAttributes(DefaultPrimaryAttributes ,	1.f);
		UOmegaFunctionLibrary::InitializeDefaultAttributes(this, OmegaASC);
	}
	else
	{
		UOmegaFunctionLibrary::InitializeAttributesFromSaveData(this, AbilitySystemComponent, SaveData);
	}
	

	OmegaGameMode->SaveInGameProgressData(SaveData);
}


void APlayerBaseCharacter::SaveProgress_Implementation(const FName& CheckpointTag)
{
	AOmegaGameMode* OmegaGameMode = Cast<AOmegaGameMode>(UGameplayStatics::GetGameMode(this));
	if (!IsValid(OmegaGameMode)) return;
	
	ULoadMenuSaveGame* SaveData = OmegaGameMode->GetInGameSaveData();
	if (!SaveData) return;

	SaveData->PlayerStartTag	= CheckpointTag;
	SaveData->Strength			= UOmegaAttributeSet::GetStrengthAttribute().GetNumericValue(GetAttributeSet());
	SaveData->Intelligence		= UOmegaAttributeSet::GetIntelligenceAttribute().GetNumericValue(GetAttributeSet());
	SaveData->Dexterity			= UOmegaAttributeSet::GetDexterityAttribute().GetNumericValue(GetAttributeSet());
	SaveData->MaxHealth			= UOmegaAttributeSet::GetMaxHealthAttribute().GetNumericValue(GetAttributeSet());
	SaveData->Health			= UOmegaAttributeSet::GetHealthAttribute().GetNumericValue(GetAttributeSet());
	SaveData->bFirstTimeLoadIn  = false;

	OmegaGameMode->SaveInGameProgressData(SaveData);
}
