#include "GameplayTags/GCCTags.h"

namespace GCCTags
{	
	namespace Abilities
	{
		namespace Common
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Death, "GCCTags.Abilities.Common.Death", "Tag/ID to identify the Death Ability")
		}
		
		namespace Player
		{
			// Version 1: Directly
			// UE_DEFINE_GAMEPLAY_TAG(Primary, "GCCTags.GCCAbilities.Primary")
			// Version 2: With a comment
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "GCCTags.Abilities.Player.Primary", "Tag/ID to identify the Primary Ability")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "GCCTags.Abilities.Player.Secondary", "Tag/ID to identify the Secondary Ability")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "GCCTags.Abilities.Player.Tertiary", "Tag/ID to identify the Tertiary Ability")
		}
		
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "GCCTags.Abilities.Enemy.HitReact", "Tag/ID to identify the HitReact Ability")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Attack, "GCCTags.Abilities.Enemy.Attack", "Tag/ID to identify the Enemy's Attack Ability")
		}

		namespace Behavior
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(ActivateOnGiven, "GCCTags.Abilities.Behavior.ActivateOnGiven", "Tag for Abilities that should activate immediately once given")
		}
	}
	
	namespace Events
	{
		namespace Common
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(KillScored, "GCCTags.Events.Common.KillScored", "Tag for a character that kill another character")
		}
		
		namespace Player
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "GCCTags.Events.Player.Primary", "Tag for the player to invoke the logic to make damage with Primary Attack")
		}
		
		namespace Enemy
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(HitReact, "GCCTags.Events.Enemy.HitReact", "Tag for the enemy when it receives something to activate HitReaction")
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(EndAttack, "GCCTags.Events.Enemy.EndAttack", "Tag for the enemy when it ends its own attack")
		}
	}
	
	namespace Status
	{
		namespace Common
		{
			UE_DEFINE_GAMEPLAY_TAG_COMMENT(Dead, "GCCTags.Status.Common.Dead", "Tag given when an object is dead")
		}
	}
	
	namespace SetByCaller
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Projectile, "GCCTags.SetByCaller.Projectile", "Tag used in projectiles for Damage value");
	}
}