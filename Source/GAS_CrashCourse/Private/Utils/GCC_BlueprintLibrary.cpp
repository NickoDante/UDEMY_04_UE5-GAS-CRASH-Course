// Nicolas Nieto - GCC - Copyright - 2026

// Header include
#include "Utils/GCC_BlueprintLibrary.h"

// Engine Includes
#include "Kismet/GameplayStatics.h"
#include "Engine/OverlapResult.h"

// Project includes
#include "AbilitySystemBlueprintLibrary.h"
#include "Characters/GCC_BaseCharacter.h"
#include "AbilitySystem/GCC_AttributeSet.h"
#include "Characters/GCC_EnemyCharacter.h"
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
	const FVector& Origin, const FName& Tag, const float SearchRange)
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
		
		// If the Distance is greater than the search range, ignore this actor.
		if (Distance > SearchRange)
		{
			continue;
		}
		
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
void UGCC_BlueprintLibrary::SendDamageEventToCharacters(TArray<AActor*> Targets,
	const TSubclassOf<UGameplayEffect>& DamageEffect, FGameplayEventData& Payload, const FGameplayTag& DataTag,
	float Damage, const FGameplayTag& EventTagOverride, UObject* OptionalParticleSystem)
{
	for (AActor* Target : Targets)
	{
		SendDamageEventToCharacter(Target, DamageEffect, Payload, DataTag, Damage, EventTagOverride, OptionalParticleSystem);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_BlueprintLibrary::SendDamageEventToCharacter(AActor* Target, const TSubclassOf<UGameplayEffect>& DamageEffect,
	FGameplayEventData& Payload, const FGameplayTag& DataTag, float Damage, const FGameplayTag& EventTagOverride, 
	UObject* OptionalParticleSystem)
{
	// Check if is a player and if its alive
	AGCC_BaseCharacter* PlayerCharacter = Cast<AGCC_BaseCharacter>(Target);
	if (!IsValid(PlayerCharacter) || !PlayerCharacter->IsAlive())
	{
		return;
	}
	
	// Set the Event Tag. 
	//	- If there's override set it directly.
	//	- If not, Get the attribute set and set it if its a Hit React or a Death tag
	FGameplayTag EventTag;
	if (!EventTagOverride.MatchesTagExact(GCCTags::None))
	{
		EventTag = EventTagOverride;
	}
	else
	{
		// Get The Attribute set to access the attributes data
		UGCC_AttributeSet* AttributeSet = Cast<UGCC_AttributeSet>(PlayerCharacter->GetAttributeSet());
		if (!IsValid(AttributeSet))
		{
			return;
		}
		
		// Check if the damage would be lethal
		const bool bIsLethal = AttributeSet->GetHealth() - Damage <= 0.0f;
	
		// Choose which event you want to send
		EventTag= bIsLethal ? GCCTags::Events::Player::Death : GCCTags::Events::Player::HitReact;
	}
	
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

//----------------------------------------------------------------------------------------------------------------------
TArray<AActor*> UGCC_BlueprintLibrary::HitBoxOverlapTest(AActor* AvatarActor, const float HitBoxRadius, 
	const float HitBoxForwardOffset, const float HitBoxElevationOffset, const bool bDrawDebugs)
{
	if (!IsValid(AvatarActor))
	{
		return TArray<AActor*>();
	}
	
	// Ensure that the overlap test ignores the Avatar Actor
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(AvatarActor);
	
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	
	// We usually work with HitResult, but for overlap test we are going to use FOverlapResults
	TArray<FOverlapResult> OverlapResults;
	FCollisionShape Sphere = FCollisionShape::MakeSphere(HitBoxRadius);
	
	// Calculate the hitbox location
	const FVector Forward = AvatarActor->GetActorForwardVector() * HitBoxForwardOffset;
	const FVector HitBoxLocation = AvatarActor->GetActorLocation() + Forward + FVector(0.f, 0.f, HitBoxElevationOffset);
	
	// Make the Overlap with the shape and the params
	UWorld* World = GEngine->GetWorldFromContextObject(AvatarActor, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))
	{
		return TArray<AActor*>();
	}
	World->OverlapMultiByChannel(OverlapResults, HitBoxLocation, FQuat::Identity, ECC_Pawn, Sphere, QueryParams, ResponseParams);
	
	// Set the actors found
	TArray<AActor*> ActorsHit;
	for (const FOverlapResult& Result : OverlapResults)
	{
		AGCC_BaseCharacter* Character = Cast<AGCC_BaseCharacter>(Result.GetActor());
		if (!IsValid(Character) || !Character->IsAlive())
		{
			continue;
		}
		
		ActorsHit.AddUnique(Character);
	}
	
	// Draw the results if needed.
	if (bDrawDebugs)
	{
		DrawHitBoxOverlapDebugs(AvatarActor, HitBoxRadius, OverlapResults, HitBoxLocation);
	}
	
	return ActorsHit;
}

//----------------------------------------------------------------------------------------------------------------------
TArray<AActor*> UGCC_BlueprintLibrary::ApplyKnockback(AActor* AvatarActor, const TArray<AActor*>& HitActors,
	const float InnerRadius, const float OuterRadius, const float LaunchForceMagnitude, const float RotationAngle,
	const bool bDrawDebugs)
{
	if (!IsValid(AvatarActor))
	{
		return TArray<AActor*>();
	}
	
	for (AActor* HitActor : HitActors)
	{
		ACharacter* HitCharacter = Cast<ACharacter>(HitActor);
		if (!IsValid(HitCharacter))
		{
			continue;
		}
		
		// Get the location of the owner and the target to apply the force
		const FVector HitCharacterLocation = HitActor->GetActorLocation();
		const FVector AvatarLocation = AvatarActor->GetActorLocation();
		
		// We want a vector from the avatar to the Hit Character because I want to launch those characters away from the avatar.
		const FVector ToHitActor = HitCharacterLocation - AvatarLocation;
		
		// Get the Distance of the vector to apply the falloff.
		const float Distance = FVector::Dist(AvatarLocation, HitCharacterLocation);
		
		// Calculate the Force to apply following the Falloff
		float LaunchForce = 0.f;
		
		// If the HitActor is far away, ignore it
		if (Distance > OuterRadius)
		{
			continue;
		}

		// If the Hit Actor is close, apply the max force
		if (Distance <= InnerRadius)
		{
			LaunchForce = LaunchForceMagnitude;
		}
		else
		{
			// Declare the falloff range from the Ineer Radius to the Outer Radius
			const FVector2D FalloffRange(InnerRadius, OuterRadius); // input range
			
			// Declare the Launch fiorce Range from the maximum to zero.
			const FVector2D LaunchForceRange(LaunchForceMagnitude, 0.f); // output range
			
			LaunchForce = FMath::GetMappedRangeValueClamped(FalloffRange, LaunchForceRange, Distance);
		}
		
		// Print the Launch force calculated if you like
		if (bDrawDebugs)
		{
			GEngine->AddOnScreenDebugMessage(
				-1, 
				3.f, 
				FColor::Red, 
				FString::Printf(TEXT("LaunchForce applied to '%s' is : %f"), *HitActor->GetName(), LaunchForce));
		}
		
		// Get the direction to apply the force, from the actor to the hit actor
		FVector KnockbackForce = ToHitActor.GetSafeNormal();
		
		// Ignore the value in Z
		KnockbackForce.Z = 0.0;
		
		// Apply the angle rotation. 
		const FVector Right = KnockbackForce.RotateAngleAxis(90.f, FVector::UpVector);
		KnockbackForce = KnockbackForce.RotateAngleAxis(-RotationAngle, Right);
		
		// We have the KnockBackForeDirection... DONT FORGET TO multiply to the Launch force !
		KnockbackForce *= LaunchForce;
		
		// Draw the force with a Debug Arrow
		if (bDrawDebugs)
		{
			UWorld* World = GEngine->GetWorldFromContextObject(AvatarActor, EGetWorldErrorMode());
			DrawDebugDirectionalArrow(
				World, 
				HitCharacterLocation, 
				HitCharacterLocation + KnockbackForce, 
				100.f, 
				FColor::Green, 
				false, 
				3.f);	
		}
		
		// Apply the force
		HitCharacter->LaunchCharacter(KnockbackForce, true, true );
		
		// If its an enemy, call the Stop Movement
		AGCC_EnemyCharacter* EnemyCharacter = Cast<AGCC_EnemyCharacter>(HitCharacter);
		if (IsValid(EnemyCharacter))
		{
			EnemyCharacter->StopMovementWhenLaunched();
		}
	}
	
	return HitActors;
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_BlueprintLibrary::DrawHitBoxOverlapDebugs(UObject* WorldContextObject, const float HitBoxRadius, 
	const TArray<FOverlapResult>& OverlapResults, const FVector& HitBoxLocation)
{
	UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))
	{
		return;
	}
	
	DrawDebugSphere(World, HitBoxLocation, HitBoxRadius, 16, FColor::Red, false, 3.f);
		
	// Draw each Overlap Result
	for (const FOverlapResult& Result : OverlapResults)
	{
		if (IsValid(Result.GetActor()))
		{
			FVector DebugLocation = Result.GetActor()->GetActorLocation();
			DebugLocation.Z += 100.f;
				
			DrawDebugSphere(World, DebugLocation, 30.f, 06, FColor::Green, false, 3.f);
		}
	}
}
