// Nicolas Nieto - GCC - Copyright - 2026

#include "GAS_CrashCourse/Public/Characters/GCC_BaseCharacter.h"

AGCC_BaseCharacter::AGCC_BaseCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	// Tick and refresh bones transforms whether rendered or not - for bone updates on a dedicated server.
	GetMesh()->VisibilityBasedAnimTickOption = EVisibilityBasedAnimTickOption::AlwaysTickPoseAndRefreshBones;
}
