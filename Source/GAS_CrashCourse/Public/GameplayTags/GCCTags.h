#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GCCTags
{
	namespace GCCAbilities
	{
		// Abilities
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tertiary);
		
		// Abilities Behavior
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ActivateOnGiven);
	}
	
	namespace GCCEvents
	{
		namespace Enemy
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact);
		}
	}
}