// Nicolas Nieto - GCC - Copyright - 2026

// Header include
#include "AbilitySystem/GCC_AttributeSet.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "GameplayEffectExtension.h"
#include "GameplayTags/GCCTags.h"
#include "Net/UnrealNetwork.h"

//----------------------------------------------------------------------------------------------------------------------
UGCC_AttributeSet::UGCC_AttributeSet()
{
	bAttributesInitialized = false;
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AttributeSet::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, bAttributesInitialized, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, Mana, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(ThisClass, MaxMana, COND_None, REPNOTIFY_Always);
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	// Health Attribute
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		// Clamp Health
		const float ClampedHealth = FMath::Clamp(GetHealth(), 0.f, GetMaxHealth());
		SetHealth(ClampedHealth);
		
		if (GetHealth() <= 0.0f)
		{
			AActor* CauserActor = Data.EffectSpec.GetEffectContext().GetInstigator();
		
			FGameplayEventData Payload;
			Payload.Instigator = Data.Target.GetAvatarActor();
		
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(CauserActor, GCCTags::Events::Common::KillScored, Payload);
		}
	}
	
	// Mana Attribute
	if (Data.EvaluatedData.Attribute == GetManaAttribute())
	{
		// Clamp Mana
		const float ClampedMana = FMath::Clamp(GetMana(), 0.f, GetMaxMana());
		SetMana(ClampedMana);
	}
	
	if (!bAttributesInitialized)
	{
		bAttributesInitialized = true;
		OnAttributesInitialized.Broadcast();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AttributeSet::OnRep_AttributesInitialized()
{
	if (bAttributesInitialized)
	{
		OnAttributesInitialized.Broadcast();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AttributeSet::OnRep_Health(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Health, OldValue);
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxHealth, OldValue);
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AttributeSet::OnRep_Mana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, Mana, OldValue);
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AttributeSet::OnRep_MaxMana(const FGameplayAttributeData& OldValue)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(ThisClass, MaxMana, OldValue);
}
