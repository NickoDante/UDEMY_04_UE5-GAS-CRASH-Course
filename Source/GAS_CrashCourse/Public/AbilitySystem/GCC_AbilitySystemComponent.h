// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "GCC_AbilitySystemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class GAS_CRASHCOURSE_API UGCC_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	
	UGCC_AbilitySystemComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
							   FActorComponentTickFunction* ThisTickFunction) override

protected:

	virtual void BeginPlay() override;

};
