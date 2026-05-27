// Nicolas Nieto - GCC - Copyright - 2026

// Header Include
#include "AbilitySystem/Abilities/Player/GCC_GA_Primary.h"

// Engine includes
#include "AbilitySystemBlueprintLibrary.h"
#include "Engine/OverlapResult.h"

// Project Includes
#include "GameplayTags/GCCTags.h"

//----------------------------------------------------------------------------------------------------------------------
UGCC_GA_Primary::UGCC_GA_Primary()
{
	HitBoxRadius = 100.f;
	HitBoxForwardOffset = 200.f;
	HitBoxElevationOffset = 20.f;
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_GA_Primary::SendHitReactEventToActors(const TArray<AActor*>& ActorsHit)
{
	for (AActor* HitActor : ActorsHit)
	{
		if (!IsValid(HitActor))
		{
			continue;
		}
		
		FGameplayEventData Payload;
		Payload.Instigator = GetAvatarActorFromActorInfo();
		
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(HitActor, GCCTags::Events::Enemy::HitReact, Payload);
	}
}
