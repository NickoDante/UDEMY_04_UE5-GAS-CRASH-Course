// Nicolas Nieto - GCC - Copyright - 2026

// Header include
#include "GAS_CrashCourse/Public/Characters/GCC_BaseCharacter.h"

// Engine includes
#include "AbilitySystemComponent.h"

//----------------------------------------------------------------------------------------------------------------------
AGCC_BaseCharacter::AGCC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Tick and refresh bones transforms whether rendered or not - for bone updates on a dedicated server.
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}

//----------------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent* AGCC_BaseCharacter::GetAbilitySystemComponent() const
{
	return nullptr;
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_BaseCharacter::GiveStartupAbilities()
{
	if (!IsValid(GetAbilitySystemComponent()))
	{
		return;
	}
	
	for (const auto& Ability : StartupAbilities)
	{
		// We get the lightweight version of the ability. This version is a struct of type FGameplayAbilitySpec
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(Ability);
		GetAbilitySystemComponent()->GiveAbility(AbilitySpec);
	}
}
