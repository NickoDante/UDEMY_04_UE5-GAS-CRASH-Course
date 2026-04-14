// Nicolas Nieto - GCC - Copyright - 2026

// Engine Includes
#include "Kismet/GameplayStatics.h"

// Project includes
#include "Utils/GCC_BlueprintLibrary.h"

#include "Characters/GCC_BaseCharacter.h"

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
