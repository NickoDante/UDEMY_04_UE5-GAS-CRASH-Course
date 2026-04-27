// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "GCC_Projectile.generated.h"

class UGameplayEffect;
class UProjectileMovementComponent;

UCLASS()
class GAS_CRASHCOURSE_API AGCC_Projectile : public AActor
{
	GENERATED_BODY()

public:

	AGCC_Projectile();
	
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	
	UFUNCTION(BlueprintCallable)
	float GetDamage() const { return Damage; }
	
protected:
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Crash|Damage", meta = (ExposeOnSpawn, ClampMin = "0.0"))
	float Damage{10.f};
	
	UFUNCTION(BlueprintImplementableEvent, Category = "Crash|Projectile")
	void BP_SpawnImpactEffects();
	
private:
	
	UPROPERTY(VisibleAnywhere, Category = "Crash|Components")
	TObjectPtr<UProjectileMovementComponent> ProjectileMovementComponent;
	
	UPROPERTY(EditDefaultsOnly, Category = "Crash|Damage")
	TSubclassOf<UGameplayEffect> DamageEffect;	
};
