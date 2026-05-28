// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "GCC_BaseCharacter.h"
#include "GCC_EnemyCharacter.generated.h"

class UAbilitySystemComponent;
class UAttributeSet;

UCLASS()
class GAS_CRASHCOURSE_API AGCC_EnemyCharacter : public AGCC_BaseCharacter
{
	GENERATED_BODY()

public:

	AGCC_EnemyCharacter();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Replicated, Category = "Crash|AI")
	uint8 bIsBeingLaunched : 1 {false} ;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual UAttributeSet* GetAttributeSet() const override;
	
	float GetAcceptanceRadius() const { return AcceptanceRadius; }
	
	float GetMinAttackDelay() const { return MinAttackDelay; }
	float GetMaxAttackDelay() const { return MinAttackDelay; }
	
	UFUNCTION(BlueprintImplementableEvent)
	float BP_GetRotationTimelineLength() const;
	
	void StopMovementWhenLaunched();

protected:
	
	virtual void BeginPlay() override;
	
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|AI")
	float AcceptanceRadius {500.0f} ;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|AI")
	float MinAttackDelay {0.1f} ;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|AI")
	float MaxAttackDelay {0.5f} ;
	
	virtual void HandleDeath() override;
	
	UFUNCTION()
	void StartMovementAfterLanded(const FHitResult& Hit);
	
private:
	
	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	UPROPERTY()
	TObjectPtr<UAttributeSet> AttributeSet;
};