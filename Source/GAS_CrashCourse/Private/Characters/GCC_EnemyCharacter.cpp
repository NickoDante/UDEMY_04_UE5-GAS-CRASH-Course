// Nicolas Nieto - GCC - Copyright - 2026

#include "Characters/GCC_EnemyCharacter.h"

#include "AbilitySystemComponent.h"

//----------------------------------------------------------------------------------------------------------------------
AGCC_EnemyCharacter::AGCC_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UAbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

//----------------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent* AGCC_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_EnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (!IsValid(GetAbilitySystemComponent()))
	{
		return;
	}
	
	GetAbilitySystemComponent()->InitAbilityActorInfo(this, this);
	
	if (!HasAuthority())
	{
		return;
	}
	
	GiveStartupAbilities();
}