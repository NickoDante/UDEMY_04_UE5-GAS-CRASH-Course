// Nicolas Nieto - GCC - Copyright - 2026

#pragma once

#include "CoreMinimal.h"
#include "GCC_BaseCharacter.h"
#include "GCC_PlayerCharacter.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class GAS_CRASHCOURSE_API AGCC_PlayerCharacter : public AGCC_BaseCharacter
{
	GENERATED_BODY()

public:

	AGCC_PlayerCharacter();
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	
	virtual UAttributeSet* GetAttributeSet() const override;
	
	virtual void PossessedBy(AController* NewController) override;
	
	virtual void OnRep_PlayerState() override;

private:
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;
	
};
