// Nicolas Nieto - GCC - Copyright - 2026

// Header Include
#include "AbilitySystem/Abilities/Player/GCC_GA_Primary.h"

// Engine includes
#include "Engine/OverlapResult.h"

//----------------------------------------------------------------------------------------------------------------------
UGCC_GA_Primary::UGCC_GA_Primary()
{
	HitBoxRadius = 100.f;
	HitBoxForwardOffset = 200.f;
	HitBoxElevationOffset = 20.f;
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_GA_Primary::HitBoxOverlapTest()
{
	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());
	
	// Ensure that the overlap test ignores the Avatar Actor
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActors(ActorsToIgnore);
	
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	
	// We usually work with HitResult, but for overlap test we are going to use FOverlapResults
	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);
	
	// Calculate the hitbox location
	const FVector Forward = GetAvatarActorFromActorInfo()->GetActorForwardVector() * HitBoxForwardOffset;
	const FVector HitBoxLocation = GetAvatarActorFromActorInfo()->GetActorLocation() + Forward + FVector(0.f, 0.f, HitBoxElevationOffset);
	
	// Make the Overlap with the shape and the params
	GetWorld()->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity, ECC_Pawn, Sphere, QueryParams, ResponseParams);
	
	// Draw the results if needed.
	if (bDrawDebugs)
	{
		DrawDebugSphere(GetWorld(), HitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.f);
		
		// Draw each Overlap Result
		for (const FOverlapResult& Result : OverlapResults)
		{
			if (IsValid(Result.GetActor()))
			{
				FVector DebugLocation = Result.GetActor()->GetActorLocation();
				DebugLocation.Z += 100.f;
				
				DrawDebugSphere(GetWorld(), DebugLocation, 30.f, 06, FColor::Green, false, 3.f);
			}
		}
	}
}
