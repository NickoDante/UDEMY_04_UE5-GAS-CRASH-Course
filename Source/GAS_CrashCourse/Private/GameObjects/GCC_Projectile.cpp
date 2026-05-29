// Nicolas Nieto - GCC - Copyright - 2026

// Header Include
#include "GameObjects/GCC_Projectile.h"

// Engine includes
#include "AbilitySystemComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"

// Project includes
#include "AbilitySystemBlueprintLibrary.h"
#include "Characters/GCC_PlayerCharacter.h"
#include "GameplayTags/GCCTags.h"
#include "Utils/GCC_BlueprintLibrary.h"

//----------------------------------------------------------------------------------------------------------------------
AGCC_Projectile::AGCC_Projectile()
{
	PrimaryActorTick.bCanEverTick = false;
	
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovementComponent");
	
	bReplicates = true;
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_Projectile::NotifyActorBeginOverlap(AActor* OtherActor)
{
	Super::NotifyActorBeginOverlap(OtherActor);
	
	AGCC_PlayerCharacter* PlayerCharacter = Cast<AGCC_PlayerCharacter>(OtherActor);
	if (!IsValid(PlayerCharacter) || !PlayerCharacter->IsAlive())
	{
		return;
	}
	
	UAbilitySystemComponent* AbilitySystemComponent = PlayerCharacter->GetAbilitySystemComponent();
	if (!IsValid(AbilitySystemComponent) || !HasAuthority())
	{
		return;
	}
	
	// Apply the Damage effect
	FGameplayEventData Payload;
	Payload.Instigator = GetOwner();
	Payload.Target = PlayerCharacter;
	UGCC_BlueprintLibrary::SendDamageEventToCharacter(
		PlayerCharacter, 
		DamageEffect, 
		Payload, 
		GCCTags::SetByCaller::Projectile, 
		Damage, 
		GCCTags::None);

	BP_SpawnImpactEffects();

	Destroy();
}
