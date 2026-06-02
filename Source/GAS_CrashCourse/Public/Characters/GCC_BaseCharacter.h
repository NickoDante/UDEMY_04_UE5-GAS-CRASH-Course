// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "GCC_BaseCharacter.generated.h"

namespace CrashTags
{
	extern GAS_CRASHCOURSE_API const FName Player;
}

class UGameplayAbility;
class UGameplayEffect;
class UAttributeSet;
struct FOnAttributeChangeData;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FASCInitialized, UAbilitySystemComponent*, ASC, UAttributeSet*, AS);

UCLASS(Abstract)
class GAS_CRASHCOURSE_API AGCC_BaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:

	AGCC_BaseCharacter();
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(BlueprintAssignable)
	FASCInitialized OnASCInitialized;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual UAttributeSet* GetAttributeSet() const { return nullptr;};
	
	bool IsAlive() const { return bAlive; }
	
	void SetIsAlive(const bool bNewValue) { bAlive = bNewValue; }
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Death")
	virtual void HandleRespawn();
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Attributes")
	void ResetAttributes();
	
	UFUNCTION(BlueprintCallable, Category = "Crash|Rotation")
	void RotateToTarget(AActor* RotateTarget);
	
	UFUNCTION(BlueprintImplementableEvent)
	void BP_RotateToTarget(AActor* RotateTarget);
	
	float GetSearchRange() const { return SearchRange; }
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|AI")
	float SearchRange {1000.f} ;
	
	void GiveStartupAbilities();
	
	void InitializeAttributes();
	
	void OnHealthChanged(const FOnAttributeChangeData& AttributeChangeData);
	
	virtual void HandleDeath();
	
private:
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Abilities")
	TArray<TSubclassOf<UGameplayAbility>> StartupAbilities;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Effects")
	TSubclassOf<UGameplayEffect> InitializeAttributesEffect;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Effects")
	TSubclassOf<UGameplayEffect> ResetAttributesEffect;
	
	UPROPERTY(Replicated, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	uint8 bAlive : 1;
	
	void ModifyAttributesByClass(TSubclassOf<UGameplayEffect> AttributeEffect);
};
