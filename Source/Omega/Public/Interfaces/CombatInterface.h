﻿#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "CombatInterface.generated.h"

UINTERFACE(BlueprintType, Blueprintable)
class UCombatInterface : public UInterface
{
	GENERATED_BODY()
};

class OMEGA_API ICombatInterface
{
	GENERATED_BODY()

public:

	virtual int32 GetPlayerLevel() const;
};
