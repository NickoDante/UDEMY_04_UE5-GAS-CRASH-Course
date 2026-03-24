// Nicolas Nieto - GCC - Copyright - 2026

#include "AbilitySystem/GCC_AbilitySystemComponent.h"
#include "GameplayTags/GCCTags.h"

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AbilitySystemComponent::OnGiveAbility(FGameplayAbilitySpec& AbilitySpec)
{
	Super::OnGiveAbility(AbilitySpec);
	
	// When a server gives an ability.
	HandleAutoActivatedAbility(AbilitySpec);
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AbilitySystemComponent::OnRep_ActivateAbilities()
{
	Super::OnRep_ActivateAbilities();
	
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec: GetActivatableAbilities())
	{
		// This is more for clients due to server is the only could receive abilities.
		HandleAutoActivatedAbility(AbilitySpec);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AbilitySystemComponent::SetAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, const int32 Level)
{
	// Check if its server only
	if (IsValid(GetAvatarActor()) && !GetAvatarActor()->HasAuthority())
	{
		return;
	}
	
	// Use FindAbilitySpecFromClass function from GAS to get the ability spec
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass);
	if (AbilitySpec)
	{
		AbilitySpec->Level = Level;
		// We want it to replicate immediately so that the new level is reflected on BPs
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AbilitySystemComponent::AddToAbilityLevel(TSubclassOf<UGameplayAbility> AbilityClass, const int32 Level)
{
	// Check if its server only
	if (IsValid(GetAvatarActor()) && !GetAvatarActor()->HasAuthority())
	{
		return;
	}
	
	// Use FindAbilitySpecFromClass function from GAS to get the ability spec
	FGameplayAbilitySpec* AbilitySpec = FindAbilitySpecFromClass(AbilityClass);
	if (AbilitySpec)
	{
		AbilitySpec->Level += Level;
		// We want it to replicate immediately so that the new level is reflected on BPs
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AbilitySystemComponent::HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!AbilitySpec.Ability)
	{
		return;
	}
	
	for (const FGameplayTag& Tag: AbilitySpec.Ability->GetAssetTags())
	{
		if (Tag.MatchesTagExact(GCCTags::Abilities::Behavior::ActivateOnGiven))
		{
			TryActivateAbility(AbilitySpec.Handle);
			return;
		}
	}
}
