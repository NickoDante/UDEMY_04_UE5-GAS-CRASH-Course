// Nicolas Nieto - GCC - Copyright - 2026


#include "AbilitySystem/Abilities/GCC_GameplayAbility.h"

//----------------------------------------------------------------------------------------------------------------------
void UGCC_GameplayAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	if (bDrawDebugs && IsValid(GEngine))
	{
		const AActor* AvatarActor = GetAvatarActorFromActorInfo();
		const FString AvatarActorName = IsValid(AvatarActor) ? AvatarActor->GetName() : "NONE";
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Green, 
			FString::Printf(TEXT("'%s' Ability Activated on %s"), *GetName(), *AvatarActorName));
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_GameplayAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	
	if (bDrawDebugs && IsValid(GEngine))
	{
		const AActor* AvatarActor = GetAvatarActorFromActorInfo();
		const FString AvatarActorName = IsValid(AvatarActor) ? AvatarActor->GetName() : "NONE";
		GEngine->AddOnScreenDebugMessage(-1, 3.f, FColor::Orange, 
			FString::Printf(TEXT("'%s' Ability Ended on %s"), *GetName(), *AvatarActorName));
	}
}
