// Nicolas Nieto - GCC - Copyright - 2026


#include "AbilitySystem/Abilities/Enemy/GCC_GA_HitReact.h"

//----------------------------------------------------------------------------------------------------------------------
void UGCC_GA_HitReact::CacheHitDirectionVectors(AActor* Instigator)
{
	// Calculate Avatar Forward
	AvatarForward = GetAvatarActorFromActorInfo()->GetActorForwardVector();
	
	// Calculate To Instigator
	const FVector AvatarLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector InstigatorLocation =Instigator->GetActorLocation();
	
	ToInstigator = InstigatorLocation - AvatarLocation;
	ToInstigator.Normalize();
}
