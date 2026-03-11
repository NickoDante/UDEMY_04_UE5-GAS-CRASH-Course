// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "GCC_AttributeSet.generated.h"

#define  ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

/**
 * The Attribute Set class for the Course.
 */
UCLASS()
class GAS_CRASHCOURSE_API UGCC_AttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
#pragma region Health
	
public:
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Health, Category = "Crash|Attributes")
	FGameplayAttributeData Health;
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldValue);
	
	ATTRIBUTE_ACCESSORS(ThisClass, Health);
	
#pragma endregion Health
#pragma region MaxHealth
	
public:
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxHealth, Category = "Crash|Attributes")
	FGameplayAttributeData MaxHealth;
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldValue);
	
	ATTRIBUTE_ACCESSORS(ThisClass, MaxHealth);
	
#pragma endregion MaxHealth
#pragma region Mana
	
public:
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mana, Category = "Crash|Attributes")
	FGameplayAttributeData Mana;
	
	UFUNCTION()
	void OnRep_Mana(const FGameplayAttributeData& OldValue);
	
	ATTRIBUTE_ACCESSORS(ThisClass, Mana);
	
#pragma endregion Mana
#pragma region MaxMana
	
public:
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMana, Category = "Crash|Attributes")
	FGameplayAttributeData MaxMana;
	
	UFUNCTION()
	void OnRep_MaxMana(const FGameplayAttributeData& OldValue);
	
	ATTRIBUTE_ACCESSORS(ThisClass, MaxMana);
	
#pragma endregion MaxMana
};
