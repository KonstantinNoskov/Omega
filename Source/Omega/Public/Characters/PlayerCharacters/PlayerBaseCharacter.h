#pragma once

#include "CoreMinimal.h"
#include "Characters/OmegaCharacter.h"
#include "PlayerBaseCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class OMEGA_API APlayerBaseCharacter : public AOmegaCharacter
{
	GENERATED_BODY()

public:
	
	APlayerBaseCharacter();
	virtual void Tick(float DeltaSeconds) override;
	virtual void PossessedBy(AController* NewController) override;

protected:

	virtual void BeginPlay() override;

#pragma region CAMERA
	
protected:

	/**
	 *	Изменяет дистанцию персонажа до камеры в зависимости от скорости передвижения персонажа. Чем быстрее движется персонаж тем дальше камера
	 * 
	 * @param DeltaTime 
	 */
	void HandleCameraBehavior(const float DeltaTime) const;
	

public:

	FORCEINLINE USpringArmComponent* GetSpringArm() const { return CharacterSpringArm; }
	FORCEINLINE UCameraComponent* GetCamera() const { return CharacterCamera; }
	

private:

	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> CharacterSpringArm;
	
	UPROPERTY(BlueprintReadOnly, VisibleAnywhere, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> CharacterCamera;
	
	float InitialCameraDistance; 

protected:

	
	/**
	 * Максимальная дистанция на которую может отдалиться камера
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterSpringArm|Omega")
	float MaxCameraDistance = 1000.f;

	
	/**
	 * Скорость с которой будет изменяться дистанция камеры
	 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = "CharacterSpringArm|Omega")
	float CameraDistanceUpdateSpeed = 1.f;

#pragma endregion

private:

	
	/**
	 * Assign owner & avatar actor to Ability system 
	 */
	void InitAbilityActorInfo();
	
};
