// Nicolas Nieto - GCC - Copyright - 2026

// Header include
#include "Utils/GCC_BlueprintLibrary.h"

// Engine Includes
#include "Kismet/GameplayStatics.h"

// Project includes
#include "AbilitySystemBlueprintLibrary.h"
#include "Characters/GCC_BaseCharacter.h"
#include "AbilitySystem/GCC_AttributeSet.h"
#include "GameplayTags/GCCTags.h"

//----------------------------------------------------------------------------------------------------------------------
EGCC_HitDirection UGCC_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot = FVector::DotProduct(TargetForward, ToInstigator);
	
	// There are on the opposite direction
	if (Dot < -0.5f)
	{
		return  EGCC_HitDirection::Back;
	}
	
	if (Dot < 0.5f)
	{
		// Either Left or Right
		const FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);
		if (Cross.Z < 0.f)
		{
			return  EGCC_HitDirection::Left;
		}
		
		return EGCC_HitDirection::Right;
	}
	
	// For other cases its going to be forward because if Dot> 0.5, both are perpendicular
	return EGCC_HitDirection::Forward;
}

//----------------------------------------------------------------------------------------------------------------------
FName UGCC_BlueprintLibrary::GetHitDirectionName(const EGCC_HitDirection& HitDirection)
{
	switch (HitDirection)
	{
		case EGCC_HitDirection::Back:
			return FName("Back");
		case EGCC_HitDirection::Left:
			return FName("Left");
		case EGCC_HitDirection::Right:
			return FName("Right");
		case EGCC_HitDirection::Forward:
			return FName("Forward");
		default:
			return FName("None");
	}
}

//----------------------------------------------------------------------------------------------------------------------
FGCC_ClosestActorWithTagResult UGCC_BlueprintLibrary::FindClosestActorWithTag(const UObject* WorldContextObject,
	const FVector& Origin, const FName& Tag)
{
	TArray<AActor*> ActorsWithTag;
	UGameplayStatics::GetAllActorsWithTag(WorldContextObject, Tag, ActorsWithTag);
	
	// Set the initial closest distance as the max value on a float
	float ClosestDistance = TNumericLimits<float>::Max();
	
	// Set the closest actor as nullptr
	AActor* ClosestActor = nullptr;
	
	// Iterate with the found actors
	for (AActor* Actor : ActorsWithTag)
	{
		if (!IsValid(Actor))
		{
			continue;
		}
		
		// Check if its a valid base character and its alive
		AGCC_BaseCharacter* BaseCharacter = Cast<AGCC_BaseCharacter>(Actor);
		if (!IsValid(BaseCharacter) || !BaseCharacter->IsAlive())
		{
			continue;
		}
		
		// Calculate the distance and check if its the closest one
		const float Distance = FVector::Dist(Origin, Actor->GetActorLocation());
		if (Distance < ClosestDistance)
		{
			ClosestDistance = Distance;
			ClosestActor = Actor;
		}
	}
	
	FGCC_ClosestActorWithTagResult Result;
	Result.Actor = ClosestActor;
	Result.Distance = ClosestDistance;
	
	return Result;
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_BlueprintLibrary::SendDamageEventToPlayer(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect,
	FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage, UObject* OptionalParticleSystem)
{
	// Check if is a player and if its alive
	AGCC_BaseCharacter* PlayerCharacter = Cast<AGCC_BaseCharacter>(Target);
	if (!IsValid(PlayerCharacter) || !PlayerCharacter->IsAlive())
	{
		return;
	}
		
	// Get The Attribute set to access the attributes data
	UGCC_AttributeSet* AttributeSet = Cast<UGCC_AttributeSet>(PlayerCharacter->GetAttributeSet());
	if (!IsValid(AttributeSet))
	{
		return;
	}
		
	// Check if the damage would be lethal
	const bool bIsLethal = AttributeSet->GetHealth() - Damage <= 0.0f;
	
	// Choose which event you want to send
	const FGameplayTag EventTag= bIsLethal ? GCCTags::Events::Player::Death : GCCTags::Events::Player::HitReact;
	
	Payload.OptionalObject = OptionalParticleSystem;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(PlayerCharacter, EventTag, Payload);
	
	// Get the ASC to apply the damage effect
	UAbilitySystemComponent* TargetASC = PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(TargetASC))
	{
		return;
	}
	
	// Set the COntext and the Spec Handle, with the effect & the level
	FGameplayEffectContextHandle ContextHandle = TargetASC->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = TargetASC->MakeOutgoingSpec(DamageEffect, 1.f, ContextHandle);
	
	// Assign the Magnitude with the tag & apply it
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DataTag, -Damage);
	TargetASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
