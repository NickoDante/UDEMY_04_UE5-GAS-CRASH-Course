// Nicolas Nieto - GCC - Copyright - 2026

// Header includes
#include "UI/GCC_WidgetComponent.h"

// Engine includes
#include "Blueprint/WidgetTree.h"

// Project Includes
#include "AbilitySystem/GCC_AbilitySystemComponent.h"
#include "AbilitySystem/GCC_AttributeSet.h"
#include "Characters/GCC_BaseCharacter.h"
#include "UI/GCC_AttributeWidget.h"

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
	for (const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair: AttributeMap)
	{
		// For checking the owned widget object
		BindWidgetToAttributeChanges(GetUserWidgetObject(), Pair);
		
		// For checking the child widget objects
		GetUserWidgetObject()->WidgetTree->ForEachWidget([this, &Pair](UWidget* ChildWidget)
		{
			BindWidgetToAttributeChanges(ChildWidget, Pair);
		});
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_WidgetComponent::BindWidgetToAttributeChanges(UWidget* WidgetObject, const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	UGCC_AttributeWidget* AttributeWidget = Cast<UGCC_AttributeWidget>(WidgetObject);
	if (!IsValid(AttributeWidget)) // We only care about CC Attribute Widgets
	{
		return;
	}
		
	if (!AttributeWidget->MatchesAttributes(Pair)) // Only subscribe for matching Attributes
	{
		return;
	}
	
	AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get()); // For initial Values
	
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(Pair.Key).AddLambda([this, AttributeWidget, &Pair](const FOnAttributeChangeData& AttributeChangeData)
	{
		AttributeWidget->OnAttributeChange(Pair, AttributeSet.Get()); // For changes during the game
	});
}
