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
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(DamageEffect, 1.f, ContextHandle);
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, GCCTags::SetByCaller::Projectile, Damage);
	
	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());

	BP_SpawnImpactEffects();

	Destroy();
}
