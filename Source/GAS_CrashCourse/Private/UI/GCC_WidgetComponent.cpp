// Nicolas Nieto - GCC - Copyright - 2026

// Header includes
#include "UI/GCC_WidgetComponent.h"

// Project Includes
#include "AbilitySystem/GCC_AbilitySystemComponent.h"
#include "AbilitySystem/GCC_AttributeSet.h"
#include "Characters/GCC_BaseCharacter.h"

//----------------------------------------------------------------------------------------------------------------------
void UGCC_WidgetComponent::BeginPlay()
{
	Super::BeginPlay();
	
	InitAbilitySystemData();
	if (!IsASCInitialized())
	{
		CrashCharacter->OnASCInitialized.AddUniqueDynamic(this, &ThisClass::OnASCInitialized);
		return;
	}
	
	InitializeAttributeDelegate();
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_WidgetComponent::InitAbilitySystemData()
{
	CrashCharacter = Cast<AGCC_BaseCharacter>(GetOwner());
	AttributeSet = Cast<UGCC_AttributeSet>(CrashCharacter->GetAttributeSet());
	AbilitySystemComponent = Cast<UGCC_AbilitySystemComponent>(CrashCharacter->GetAbilitySystemComponent());
}

//----------------------------------------------------------------------------------------------------------------------
bool UGCC_WidgetComponent::IsASCInitialized() const
{
	return AbilitySystemComponent.IsValid() && AttributeSet.IsValid();
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_WidgetComponent::OnASCInitialized(UAbilitySystemComponent* ASC, UAttributeSet* AS)
{
	AbilitySystemComponent = Cast<UGCC_AbilitySystemComponent>(ASC);
	AttributeSet = Cast<UGCC_AttributeSet>(AS);
	
	if (!IsASCInitialized())
	{
		return;
	}
	
	InitializeAttributeDelegate();
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_WidgetComponent::InitializeAttributeDelegate()
{
	if (!AttributeSet.IsValid())
	{
		return;
	}
	
	if (!AttributeSet->bAttributesInitialized)
	{
		AttributeSet->OnAttributesInitialized.AddUniqueDynamic(this, &ThisClass::UGCC_WidgetComponent::BindToAttributeChanges);
	}
	else
	{
		BindToAttributeChanges();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_WidgetComponent::BindToAttributeChanges()
{
	// TODO: Listen for changes to gameplay attributes and update our widgets accordingly
}
