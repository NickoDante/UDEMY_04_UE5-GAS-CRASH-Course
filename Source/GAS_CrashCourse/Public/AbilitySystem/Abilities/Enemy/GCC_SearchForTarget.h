// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/GCC_GameplayAbility.h"
#include "GCC_SearchForTarget.generated.h"

class AGCC_BaseCharacter;
class UGCC_WaitGameplayEvent;
class AGCC_EnemyCharacter;
/**
 * 
 */
UCLASS()
class GAS_CRASHCOURSE_API UGCC_SearchForTarget : public UGCC_GameplayAbility
{
	GENERATED_BODY()
	
public:
	
	UGCC_SearchForTarget();
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

private:
	
	TWeakObjectPtr<AGCC_EnemyCharacter> OwningEnemyPtr;
	TWeakObjectPtr<AAIController> OwningAIControllerPtr;
	TWeakObjectPtr<AGCC_BaseCharacter> TargetBaseCharacterPtr;
	
	UPROPERTY()
	TObjectPtr<UGCC_WaitGameplayEvent> WaitGameplayEventTask;
	
	UPROPERTY()
	TObjectPtr<UAbilityTask_WaitDelay> SearchDelayTask;
	
	void StartSearch();
	
	UFUNCTION()
	void EndAttackEventReceived(FGameplayEventData Payload);
	
	UFUNCTION()
	void Search();
	
	void MoveToTargetAndAttack();
};
