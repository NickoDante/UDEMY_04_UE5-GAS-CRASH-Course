// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "GCC_GameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class GAS_CRASHCOURSE_API UGCC_GameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crash|Debug")
	uint8 bDrawDebugs : 1;
};
