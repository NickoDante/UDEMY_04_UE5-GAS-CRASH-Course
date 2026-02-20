// Nicolas Nieto - GCC - Copyright - 2026

#include "Player/GCC_PlayerState.h"
#include "AbilitySystem/GCC_AbilitySystemComponent.h"

//----------------------------------------------------------------------------------------------------------------------
AGCC_PlayerState::AGCC_PlayerState()
{
	// To update frequently the player up to default values.
	SetNetUpdateFrequency(100.f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UGCC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

//----------------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent* AGCC_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
