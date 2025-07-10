#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "OmegaWidgetComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable, BlueprintType)
class OMEGA_API UOmegaWidgetComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:

	UOmegaWidgetComponent();

protected:

	virtual void BeginPlay() override;

};
