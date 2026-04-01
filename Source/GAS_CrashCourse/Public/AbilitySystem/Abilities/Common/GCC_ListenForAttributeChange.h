// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GCC_GameplayAbility.h"
#include "GCC_ListenForAttributeChange.generated.h"

/**
 * The Ability to listen any Attribute changing its own value
 */
UCLASS()
class GAS_CRASHCOURSE_API UGCC_ListenForAttributeChange : public UGCC_GameplayAbility
{
	GENERATED_BODY()
	
protected:
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Crash|Ability")
	FGameplayAttribute Attribute;
};
