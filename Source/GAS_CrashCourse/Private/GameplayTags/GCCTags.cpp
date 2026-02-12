#include "GameplayTags/GCCTags.h"

namespace GCCTags
{
	namespace GCCAbilities
	{
		// Version 1: Directly
		// UE_DEFINE_GAMEPLAY_TAG(Primary, "GCCTags.GCCAbilities.Primary")
		// Version 2: With a comment
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Primary, "GCCTags.GCCAbilities.Primary", "Tag for the Primary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Secondary, "GCCTags.GCCAbilities.Secondary", "Tag for the Secondary Ability")
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Tertiary, "GCCTags.GCCAbilities.Tertiary", "Tag for the Tertiary Ability")
	}
}