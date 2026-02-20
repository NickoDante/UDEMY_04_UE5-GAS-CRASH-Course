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
void UGCC_AbilitySystemComponent::HandleAutoActivatedAbility(const FGameplayAbilitySpec& AbilitySpec)
{
	if (!AbilitySpec.Ability)
	{
		return;
	}
	
	for (const FGameplayTag& Tag: AbilitySpec.Ability->GetAssetTags())
	{
		if (Tag.MatchesTagExact(GCCTags::GCCAbilities::ActivateOnGiven))
		{
			TryActivateAbility(AbilitySpec.Handle);
			return;
		}
	}
}
