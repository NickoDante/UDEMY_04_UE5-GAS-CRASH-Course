// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GCC_BaseCharacter.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS(Abstract)
class GAS_CRASHCOURSE_API AGCC_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AGCC_BaseCharacter();
	
	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual UAttributeSet* GetAttributeSet() const { return nullptr;};
	
protected:
	
	void GiveStartupAbilities();
	
	void InitializeAttributes();
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Effects")
	TSubclassOf<UGameplayEffect> InitializeAttributesEffect;
};
