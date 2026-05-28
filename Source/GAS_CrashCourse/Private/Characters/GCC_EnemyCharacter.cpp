// Nicolas Nieto - GCC - Copyright - 2026

// Header Include
#include "Characters/GCC_EnemyCharacter.h"

// Engine Includes
#include "Runtime/AIModule/Classes/AIController.h"

// Project Includes
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystem/GCC_AbilitySystemComponent.h"
#include "AbilitySystem/GCC_AttributeSet.h"
#include "GameplayTags/GCCTags.h"
#include "Net/UnrealNetwork.h"

//----------------------------------------------------------------------------------------------------------------------
AGCC_EnemyCharacter::AGCC_EnemyCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	AbilitySystemComponent = CreateDefaultSubobject<UGCC_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
	
	AttributeSet = CreateDefaultSubobject<UGCC_AttributeSet>("AttributeSet");
}

//----------------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent* AGCC_EnemyCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

//----------------------------------------------------------------------------------------------------------------------
UAttributeSet* AGCC_EnemyCharacter::GetAttributeSet() const
{
	return AttributeSet;
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
	OnASCInitialized.Broadcast(GetAbilitySystemComponent(), GetAttributeSet());
	
	if (!HasAuthority())
	{
		return;
	}
	
	GiveStartupAbilities();
	InitializeAttributes();
	
	UGCC_AttributeSet* GCC_AttributeSet = Cast<UGCC_AttributeSet>(GetAttributeSet());
	if (!IsValid(GCC_AttributeSet))
	{
		return;
	}
	
	GetAbilitySystemComponent()->GetGameplayAttributeValueChangeDelegate(GCC_AttributeSet->GetHealthAttribute()).AddUObject(this, &ThisClass::OnHealthChanged);
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_EnemyCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, bIsBeingLaunched);
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_EnemyCharacter::HandleDeath()
{
	Super::HandleDeath();
	
	AAIController* AIController = GetController<AAIController>();
	if (!IsValid(AIController))
	{
		return;
	}
	
	AIController->StopMovement();
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_EnemyCharacter::StopMovementWhenLaunched()
{
	bIsBeingLaunched = true;
	
	AAIController* AIController = GetController<AAIController>();
	if (!IsValid(AIController))
	{
		return;
	}
	
	AIController->StopMovement();
	
	if (!LandedDelegate.IsAlreadyBound(this, &ThisClass::StartMovementAfterLanded))
	{
		LandedDelegate.AddUniqueDynamic(this, &ThisClass::StartMovementAfterLanded);
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_EnemyCharacter::StartMovementAfterLanded(const FHitResult& Hit)
{
	bIsBeingLaunched = false;
	
	// Send the event to search again when its in the ground. No GameplayEventData needed.
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, GCCTags::Events::Enemy::EndAttack, FGameplayEventData());
	
	// Clean the Delegate subscription
	LandedDelegate.RemoveAll(this);
}

