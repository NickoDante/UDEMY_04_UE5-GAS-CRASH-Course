// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GCC_GameplayAbility.h"
#include "GCC_GA_Primary.generated.h"

/**
 * The class for the Player's Primary Ability
 */
UCLASS()
class GAS_CRASHCOURSE_API UGCC_GA_Primary : public UGCC_GameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UGCC_GA_Primary();
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Abilities")
	void HitBoxOverlapTest();
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category="Crash|Abilities")
	float HitBoxRadius;
	
	UPROPERTY(EditDefaultsOnly, Category="Crash|Abilities")
	float HitBoxForwardOffset;
	
	UPROPERTY(EditDefaultsOnly, Category="Crash|Abilities")
	float HitBoxElevationOffset;
};
