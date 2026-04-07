#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace GCCTags
{
	// Category for anything involves Abilities
	namespace Abilities
	{
		// Category for anything about Players & Enemies = Entities
		namespace Common
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Death);
		}
		
		// Category for anything about Player Ability
		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Secondary);
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Tertiary);
		}
		
		// Category for anything about Enemy Ability
		namespace Enemy
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact);
		}

		// Category for anything about Global Ability Behaviors
		namespace Behavior
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(ActivateOnGiven);
		}
	}
	
	// Category for anything involves Events
	namespace Events
	{
		// Events for the player
		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary); // Called when the primary action animation is played and its in the time to make a hit
		}
		
		// Events for the enemy
		namespace Enemy
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact); // Called when the enemy has been involved when a hit occurs.
		}
	}
}