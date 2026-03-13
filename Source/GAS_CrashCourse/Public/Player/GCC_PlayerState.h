// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AbilitySystemInterface.h"

#include "GCC_PlayerState.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

/**
 * The Player State for the Crash Course
 */
UCLASS()
class GAS_CRASHCOURSE_API AGCC_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	
	AGCC_PlayerState();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	UAttributeSet* GetAttributeSet() const { return AttributeSet; };
	
private:
	
	UPROPERTY(VisibleAnywhere, Category = "Crash|Abilities")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};
