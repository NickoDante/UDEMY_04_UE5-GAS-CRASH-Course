// Nicolas Nieto - GCC - Copyright - 2026

// Header Include

#include "AbilitySystem/Abilities/Enemy/GCC_SearchForTarget.h"

// Engine includes
#include "AIController.h"
#include "Abilities/Tasks/AbilityTask_WaitDelay.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Tasks/AITask_MoveTo.h"
#include "AbilitySystemComponent.h"

// Project includes
#include "AbilitySystem/AbilityTasks/GCC_WaitGameplayEvent.h"
#include "Characters/GCC_EnemyCharacter.h"
#include "GameplayTags/GCCTags.h"
#include "Utils/GCC_BlueprintLibrary.h"

//----------------------------------------------------------------------------------------------------------------------
UGCC_SearchForTarget::UGCC_SearchForTarget()
{
	InstancingPolicy = EGameplayAbilityInstancingPolicy::InstancedPerActor;
	NetExecutionPolicy = EGameplayAbilityNetExecutionPolicy::ServerOnly;
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_SearchForTarget::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	
	OwningEnemyPtr = Cast<AGCC_EnemyCharacter>(GetAvatarActorFromActorInfo());
	check(OwningEnemyPtr.IsValid());
	OwningAIControllerPtr = Cast<AAIController>(OwningEnemyPtr->GetController());
	check(OwningAIControllerPtr.IsValid());
	
	StartSearch();
	
	WaitGameplayEventTask = UGCC_WaitGameplayEvent::WaitGameplayEventToActorProxy(
		GetAvatarActorFromActorInfo(),
		GCCTags::Events::Enemy::EndAttack
		);
	WaitGameplayEventTask->EventReceived.AddUniqueDynamic(this, &ThisClass::EndAttackEventReceived);
	WaitGameplayEventTask->StartActivation();
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_SearchForTarget::StartSearch()
{
	if (bDrawDebugs)
	{
		GEngine->AddOnScreenDebugMessage(-1, 3.0f, FColor::Red, FString::Printf(TEXT("UGCC_SearchForTarget::StartSearch -> Searching for target")));
	}
	
	if (!OwningEnemyPtr.IsValid())
	{
		return;
	}
	
	const float SearchDelay = FMath::RandRange(OwningEnemyPtr->GetMinAttackDelay(), OwningEnemyPtr->GetMaxAttackDelay());
	SearchDelayTask = UAbilityTask_WaitDelay::WaitDelay(
		this,
		SearchDelay
		);
	SearchDelayTask->OnFinish.AddUniqueDynamic(this, &ThisClass::Search);
	SearchDelayTask->Activate();
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_SearchForTarget::EndAttackEventReceived(FGameplayEventData Payload)
{
	if (OwningEnemyPtr.IsValid() && !OwningEnemyPtr->bIsBeingLaunched)
	{
		StartSearch();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_SearchForTarget::Search()
{
	const FVector SearchOrigin = GetAvatarActorFromActorInfo()->GetActorLocation();
	FGCC_ClosestActorWithTagResult ClosestActorResult =  UGCC_BlueprintLibrary::FindClosestActorWithTag(this, SearchOrigin, CrashTags::Player);
	
	TargetBaseCharacterPtr = Cast<AGCC_BaseCharacter>(ClosestActorResult.Actor);
	
	if (!TargetBaseCharacterPtr.IsValid())
	{
		StartSearch();
		return;
	}
	
	if (bDrawDebugs)
	{
		UKismetSystemLibrary::DrawDebugSphere(
			this,
			TargetBaseCharacterPtr->GetActorLocation() + FVector(0.0f, 0.0f, 200.0f),
			10, 
			12,
			FColor::Cyan,
			10
			);
	}
	
	if (TargetBaseCharacterPtr->IsAlive())
	{
		MoveToTargetAndAttack();
	}
	else
	{
		StartSearch();
	}
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_SearchForTarget::MoveToTargetAndAttack()
{
	if (!OwningEnemyPtr.IsValid() || !OwningAIControllerPtr.IsValid() || !TargetBaseCharacterPtr.IsValid())
	{
		return;
	}
	
	if (!OwningEnemyPtr->IsAlive())
	{
		StartSearch();
		return;
	}
	
	MoveToLocationOrActorTask = UAITask_MoveTo::AIMoveTo(
		OwningAIControllerPtr.Get(),
		FVector(),
		TargetBaseCharacterPtr.Get(),
		OwningEnemyPtr->GetAcceptanceRadius()
		);
	
	MoveToLocationOrActorTask->OnMoveTaskFinished.AddUObject(this, &ThisClass::RotationAndAttack);
	MoveToLocationOrActorTask->ConditionalPerformMove();
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_SearchForTarget::RotationAndAttack(TEnumAsByte<EPathFollowingResult::Type> Result, AAIController* AIController)
{
	if (Result != EPathFollowingResult::Success)
	{
		StartSearch();
		return;
	}
	
	if (!OwningEnemyPtr.IsValid())
	{
		return;
	}
	
	OwningEnemyPtr->RotateToTarget(TargetBaseCharacterPtr.Get());
	
	AttackRotationDelayTask = UAbilityTask_WaitDelay::WaitDelay(
		this,
		OwningEnemyPtr.Get()->BP_GetRotationTimelineLength()
		);
	AttackRotationDelayTask->OnFinish.AddUniqueDynamic(this, &ThisClass::AttackTarget);
	AttackRotationDelayTask->Activate();
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_SearchForTarget::AttackTarget()
{
	UAbilitySystemComponent* ASC = GetAbilitySystemComponentFromActorInfo();
	if (!IsValid(ASC))
	{
		return;
	}
	
	const FGameplayTag AttackTag = GCCTags::Abilities::Enemy::Attack;
	ASC->TryActivateAbilitiesByTag(AttackTag.GetSingleTagContainer());
}
