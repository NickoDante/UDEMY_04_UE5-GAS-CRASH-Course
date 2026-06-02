// Nicolas Nieto - GCC - Copyright - 2026

// Header include
#include "UI/GCC_AttributeWidget.h"

//----------------------------------------------------------------------------------------------------------------------
void UGCC_AttributeWidget::OnAttributeChange(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair,
	UGCC_AttributeSet* AttributeSet, const float OldValue)
{
	// This returns the numeric value of the attributes
	const float AttributeValue = Pair.Key.GetNumericValue(AttributeSet);
	const float MaxAttributeValue = Pair.Value.GetNumericValue(AttributeSet);
	
	BP_OnAttributeChange(AttributeValue, MaxAttributeValue, OldValue);
}

//----------------------------------------------------------------------------------------------------------------------
bool UGCC_AttributeWidget::MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const
{
	return Attribute == Pair.Key && MaxAttribute == Pair.Value;
}
