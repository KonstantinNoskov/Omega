#pragma once

#include "CoreMinimal.h"
#include "Characters/OmegaCharacter.h"
#include "RedHoodCharacter.generated.h"

class UCameraComponent;
class USpringArmComponent;

UCLASS()
class OMEGA_API ARedHoodCharacter : public AOmegaCharacter
{
	GENERATED_BODY()

public:

	ARedHoodCharacter();
	virtual void Tick(float DeltaSeconds) override;

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
	
};
