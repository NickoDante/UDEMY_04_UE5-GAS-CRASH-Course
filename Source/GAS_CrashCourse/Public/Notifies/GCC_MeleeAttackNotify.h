// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "GCC_MeleeAttackNotify.generated.h"

/**
 * 
 */
UCLASS()
class GAS_CRASHCOURSE_API UGCC_MeleeAttackNotify : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	
	virtual void NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime, const FAnimNotifyEventReference& EventReference) override;	

private:
	
	UPROPERTY(EditAnywhere, Category = "Crash|Debug")
	bool bDrawDebugs;
	
	UPROPERTY(EditAnywhere, Category = "Crash|Sockets")
	FName SocketName{"FX_Trail_01_R"};
	
	UPROPERTY(EditAnywhere, Category = "Crash|Sockets")
	float SocketExtensionOffset{40.0f};
	
	UPROPERTY(EditAnywhere, Category = "Crash|Sockets")
	float SphereTraceRadius{60.0f};
	
	void PerformSphereTrace(TArray<FHitResult>& OutHits, USkeletalMeshComponent* MeshComponent) const;
	
	void SendEventsToActors(const TArray<FHitResult>& Hits, USkeletalMeshComponent* MeshComponent) const;
};
