// Nicolas Nieto - GCC - Copyright - 2026


#include "Utils/GCC_BlueprintLibrary.h"

//----------------------------------------------------------------------------------------------------------------------
EGCC_HitDirection UGCC_BlueprintLibrary::GetHitDirection(const FVector& TargetForward, const FVector& ToInstigator)
{
	const float Dot = FVector::DotProduct(TargetForward, ToInstigator);
	
	// There are on the opposite direction
	if (Dot < -0.5f)
	{
		return  EGCC_HitDirection::Back;
	}
	
	if (Dot < 0.5f)
	{
		// Either Left or Right
		const FVector Cross = FVector::CrossProduct(TargetForward, ToInstigator);
		if (Cross.Z < 0.f)
		{
			return  EGCC_HitDirection::Left;
		}
		
		return EGCC_HitDirection::Right;
	}
	
	// For other cases its going to be forward because if Dot> 0.5, both are perpendicular
	return EGCC_HitDirection::Forward;
}

//----------------------------------------------------------------------------------------------------------------------
FName UGCC_BlueprintLibrary::GetHitDirectionName(const EGCC_HitDirection& HitDirection)
{
	switch (HitDirection)
	{
		case EGCC_HitDirection::Back:
			return FName("Back");
		case EGCC_HitDirection::Left:
			return FName("Left");
		case EGCC_HitDirection::Right:
			return FName("Right");
		case EGCC_HitDirection::Forward:
			return FName("Forward");
		default:
			return FName("None");
	}
}
