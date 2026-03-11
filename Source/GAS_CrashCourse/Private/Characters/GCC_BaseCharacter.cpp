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

//----------------------------------------------------------------------------------------------------------------------
void AGCC_BaseCharacter::InitializeAttributes()
{
	// Check first if the effect exist
	checkf(IsValid(InitializeAttributesEffect), TEXT("InitializeAttributes not set!"));
	
	/* Apply the effect:
	*	1. Make an effect Context handle
	*	2. Make an Spec from the effect class, the level and the context handle
	*	3. Apply the effect to Self (the ASC who is calling it)
	*/
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(InitializeAttributesEffect, 1.f, ContextHandle);
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}
