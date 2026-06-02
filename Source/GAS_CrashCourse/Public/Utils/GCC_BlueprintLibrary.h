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

USTRUCT(BlueprintType)
struct FGCC_ClosestActorWithTagResult
{
	GENERATED_BODY()
	
	UPROPERTY(BlueprintReadWrite)
	TWeakObjectPtr<AActor> Actor;
	
	UPROPERTY(BlueprintReadWrite)
	float Distance {0.0f};
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
	
	UFUNCTION(BlueprintCallable)
	static FGCC_ClosestActorWithTagResult FindClosestActorWithTag(const UObject* WorldContextObject, const FVector& Origin, const FName& Tag, const float SearchRange);
	
	UFUNCTION(BlueprintCallable)
	static void SendDamageEventToCharacters(TArray<AActor*> Targets, const TSubclassOf<UGameplayEffect>& DamageEffect,
		UPARAM(ref) FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage, const FGameplayTag& EventTagOverride, 
		UObject* OptionalParticleSystem = nullptr);
	
	UFUNCTION(BlueprintCallable)
	static void SendDamageEventToCharacter(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect,
		UPARAM(ref) FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage, const FGameplayTag& EventTagOverride, 
		UObject* OptionalParticleSystem = nullptr);
		
	UFUNCTION(BlueprintCallable)
	static TArray<AActor*> HitBoxOverlapTest(AActor* AvatarActor, const float HitBoxRadius, 
		const float HitBoxForwardOffset = 0.f, const float HitBoxElevationOffset = 0.f, const bool bDrawDebugs = false);
	
	UFUNCTION(BlueprintCallable)
	static TArray<AActor*> ApplyKnockback(AActor* AvatarActor, const TArray<AActor*>& HitActors, const float InnerRadius, 
		const float OuterRadius, const float LaunchForceMagnitude, const float RotationAngle = 45.f, const bool bDrawDebugs = false);
	
protected:
	
	static void DrawHitBoxOverlapDebugs(UObject* WorldContextObject, const float HitBoxRadius, const TArray<FOverlapResult>& OverlapResults, 
		const FVector& HitBoxLocation);
};
