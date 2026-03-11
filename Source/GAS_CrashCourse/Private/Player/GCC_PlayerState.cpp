// Nicolas Nieto - GCC - Copyright - 2026

// Header Include
#include "Player/GCC_PlayerState.h"

// Project Includes
#include "AbilitySystem/GCC_AbilitySystemComponent.h"
#include "AbilitySystem/GCC_AttributeSet.h"

//----------------------------------------------------------------------------------------------------------------------
AGCC_PlayerState::AGCC_PlayerState()
{
	// To update frequently the player up to default values.
	SetNetUpdateFrequency(100.f);
	
	AbilitySystemComponent = CreateDefaultSubobject<UGCC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
	
	AttributeSet = CreateDefaultSubobject<UGCC_AttributeSet>("AttributeSet");
}

//----------------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent* AGCC_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}
