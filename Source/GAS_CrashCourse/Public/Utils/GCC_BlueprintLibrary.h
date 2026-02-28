// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "GCC_BlueprintLibrary.generated.h"

UENUM(BlueprintType)
enum class EGCC_HitDirection : uint8
{
	Left,
	Right,
	Forward,
	Back
};

/**
 * The Blueprint Function library for global functions on the GCC Project
 */
UCLASS()
class GAS_CRASHCOURSE_API UGCC_BlueprintLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure)
	static EGCC_HitDirection GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator);
	
	UFUNCTION(BlueprintPure)
	static FName GetHitDirectionName(const EGCC_HitDirection& HitDirection);
};
