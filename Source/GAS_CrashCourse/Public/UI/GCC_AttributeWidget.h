// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "AbilitySystem/GCC_AttributeSet.h"

#include "GCC_AttributeWidget.generated.h"

/**
 * The Widget Class for any Attribute
 */
UCLASS()
class GAS_CRASHCOURSE_API UGCC_AttributeWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Crash|Attributes")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Crash|Attributes")
	FGameplayAttribute MaxAttribute;
	
	
	void OnAttributeChange(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair, UGCC_AttributeSet* AttributeSet); 
			// We need the AttributeSet in order to access the numerical value of any gameplay attribute
			// FGameplatyAttribute is just an identifier, that tells us which attribute we're dealing with
	
	bool MatchesAttributes(const TTuple<FGameplayAttribute, FGameplayAttribute>& Pair) const;
	
	UFUNCTION(BlueprintImplementableEvent, meta = (DisplayName = "On Attribute Change"))
	void BP_OnAttributeChange(const float NewValue, const float NewMaxValue);
};
