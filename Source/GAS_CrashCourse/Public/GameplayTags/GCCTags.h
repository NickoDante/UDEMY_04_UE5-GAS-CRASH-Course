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
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attack);
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
		// Events for tCommon usage: Player & Enemies
		namespace Common
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(KillScored); // Called when a character kill another character
		}
		
		// Events for the player
		namespace Player
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Primary); // Called when the primary action animation is played and its in the time to make a hit
		}
		
		// Events for the enemy
		namespace Enemy
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(HitReact); // Called when the enemy has been involved when a hit occurs.
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(EndAttack); // Called when the enemy ends its attack.
		}
	}
	
	// Category for anything involves Status
	namespace Status
	{
		// Statuses for any object in the game
		namespace Common
		{
			UE_DECLARE_GAMEPLAY_TAG_EXTERN(Dead); // When an object is dead
		}
	}
}