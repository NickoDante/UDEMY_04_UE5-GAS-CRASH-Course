// Nicolas Nieto - GCC - Copyright - 2026

// Header include
#include "GAS_CrashCourse/Public/Characters/GCC_BaseCharacter.h"

// Engine includes
#include "AbilitySystemComponent.h"
#include "Net/UnrealNetwork.h"

//----------------------------------------------------------------------------------------------------------------------
namespace CrashTags
{
	const FName Player = FName("Player");
}

//----------------------------------------------------------------------------------------------------------------------
AGCC_BaseCharacter::AGCC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Tick and refresh bones transforms whether rendered or not - for bone updates on a dedicated server.
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
	
	bAlive = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_BaseCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass, bAlive);
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
	checkf(IsValid(InitializeAttributesEffect), TEXT("InitializeAttributesEffect not set!"));
	ModifyAttributesByClass(InitializeAttributesEffect);
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_BaseCharacter::OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData)
{
	if (AttributeChangeData.NewValue <= 0.f)
	{
		HandleDeath();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_BaseCharacter::HandleDeath()
{
	SetIsAlive(false);
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_BaseCharacter::ModifyAttributesByClass(TSubclassOf<UGameplayEffect> AttributeEffect)
{
	/* Apply the effect:
	*	1. Make an effect Context handle
	*	2. Make an Spec from the effect class, the level and the context handle
	*	3. Apply the effect to Self (the ASC who is calling it)
	*/
	if (!IsValid(GetAbilitySystemComponent()))
	{
		return;
	}
	
	FGameplayEffectContextHandle ContextHandle = GetAbilitySystemComponent()->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = GetAbilitySystemComponent()->MakeOutgoingSpec(AttributeEffect, 1.f, ContextHandle);
	
	GetAbilitySystemComponent()->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_BaseCharacter::HandleRespawn()
{
	SetIsAlive(true);
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_BaseCharacter::ResetAttributes()
{
	// Check if the effect exist
	checkf(IsValid(ResetAttributesEffect), TEXT("ResetAttributeEffect not set!"));
	ModifyAttributesByClass(ResetAttributesEffect);
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_BaseCharacter::RotateToTarget(AActor* RotateTarget)
{
	BP_RotateToTarget(RotateTarget);
}
