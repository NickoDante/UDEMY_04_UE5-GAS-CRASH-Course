// Nicolas Nieto - GCC - Copyright - 2026


#include "Notifies/GCC_MeleeAttackNotify.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "KismetTraceUtils.h"
#include "Characters/GCC_PlayerCharacter.h"
#include "GameplayTags/GCCTags.h"
#include "Kismet/KismetMathLibrary.h"

void UGCC_MeleeAttackNotify::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation,
                                        float FrameDeltaTime, const FAnimNotifyEventReference& EventReference)
{
	Super::NotifyTick(MeshComp, Animation, FrameDeltaTime, EventReference);
	
	if (!IsValid(MeshComp))
	{
		return;
	}
	
	if (!IsValid(MeshComp->GetOwner()))
	{
		return;
	}
	
	TArray<FHitResult> HitResults;
	PerformSphereTrace(HitResults, MeshComp);
	SendEventsToActors(HitResults, MeshComp);		
}

void UGCC_MeleeAttackNotify::PerformSphereTrace(TArray<FHitResult>& OutHits, USkeletalMeshComponent* MeshComponent) const
{
	// Calculate Start
	const FTransform SocketTransform = MeshComponent->GetSocketTransform(SocketName);
	const FVector Start = SocketTransform.GetLocation();
	
	// Calculate End
	const FVector ExtendedSocketDirection = UKismetMathLibrary::GetForwardVector(SocketTransform.GetRotation().Rotator()) * SocketExtensionOffset;
	const FVector End = Start - ExtendedSocketDirection;
	
	// Create actors to ignore
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(MeshComponent->GetOwner());
	
	// Set the collision response
	FCollisionResponseParams ResponseParams;
	ResponseParams.CollisionResponse.SetAllChannels(ECR_Ignore);
	ResponseParams.CollisionResponse.SetResponse(ECC_Pawn, ECR_Block);
	
	// Make the trace
	UWorld* World = GEngine->GetWorldFromContextObject(MeshComponent, EGetWorldErrorMode::LogAndReturnNull);
	if (!IsValid(World))
	{
		return;
	}
	
	const bool bHit = World->SweepMultiByChannel(
		OutHits, 
		Start, 
		End, 
		FQuat::Identity, 
		ECC_Visibility, 
		FCollisionShape::MakeSphere(SphereTraceRadius), 
		Params, 
		ResponseParams);
	
	if (bDrawDebugs)
	{
		DrawDebugSphereTraceMulti(
			World, 
			Start, 
			End, 
			SphereTraceRadius, 
			EDrawDebugTrace::ForDuration, 
			bHit, 
			OutHits, 
			FColor::Green, 
			FColor::Red, 
			5.0f);
	}
}

void UGCC_MeleeAttackNotify::SendEventsToActors(const TArray<FHitResult>& Hits, USkeletalMeshComponent* MeshComponent) const
{
	for (FHitResult Hit: Hits)
	{
		AGCC_PlayerCharacter* PlayerCharacter = Cast<AGCC_PlayerCharacter>(Hit.GetActor());
		if (!IsValid(PlayerCharacter))
		{
			continue;
		}
		
		if (!PlayerCharacter->IsAlive())
		{
			continue;
		}
		
		UAbilitySystemComponent* ASC = PlayerCharacter->GetAbilitySystemComponent();
		if (!IsValid(ASC))
		{
			continue;
		}
		
		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		ContextHandle.AddHitResult(Hit);
		
		FGameplayEventData Payload;
		Payload.Target = PlayerCharacter;
		Payload.ContextHandle = ContextHandle;
		Payload.Instigator = MeshComponent->GetOwner();
		
		FGameplayTag TraceHitTag = GCCTags::Events::Enemy::Melee::TraceHit;
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(MeshComponent->GetOwner(), TraceHitTag, Payload);
	}
}
