// Nicolas Nieto - GCC - Copyright - 2026

// Header include
#include "AbilitySystem/AbilityTasks/GCC_WaitGameplayEvent.h"

//----------------------------------------------------------------------------------------------------------------------
UGCC_WaitGameplayEvent* UGCC_WaitGameplayEvent::WaitGameplayEventToActorProxy(AActor* TargetActor,
	FGameplayTag EventTag, bool OnlyTriggerOnce, bool OnlyMatchExact)
{
	UGCC_WaitGameplayEvent* MyObj = NewObject<UGCC_WaitGameplayEvent>();
	MyObj->SetAbilityActor(TargetActor);
	MyObj->Tag = EventTag;
	MyObj->OnlyTriggerOnce = OnlyTriggerOnce;
	MyObj->OnlyMatchExact = OnlyMatchExact;
	return MyObj;
}

//----------------------------------------------------------------------------------------------------------------------
void UGCC_WaitGameplayEvent::StartActivation()
{
	Activate();
}
