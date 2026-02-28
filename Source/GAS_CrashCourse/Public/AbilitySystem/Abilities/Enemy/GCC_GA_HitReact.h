// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GCC_GameplayAbility.h"
#include "GCC_GA_HitReact.generated.h"

/**
 * Class fo the Enemy Hit React ability 
 */
UCLASS()
class GAS_CRASHCOURSE_API UGCC_GA_HitReact : public UGCC_GameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(BlueprintReadWrite, Category="Crash|Abilities")
	FVector AvatarForward;
	
	UPROPERTY(BlueprintReadWrite, Category="Crash|Abilities")
	FVector ToInstigator;
	
	UFUNCTION(BlueprintCallable, Category="Crash|Abilities")
	void CacheHitDirectionVectors(AActor* Instigator);
};
