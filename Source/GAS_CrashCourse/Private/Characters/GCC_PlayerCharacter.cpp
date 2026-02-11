// Nicolas Nieto - GCC - Copyright - 2026

// Header include
#include "GAS_CrashCourse/Public/Characters/GCC_PlayerCharacter.h"

// Engine includes
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "AbilitySystemComponent.h"

// Project Includes
#include "Player/GCC_PlayerState.h"

//----------------------------------------------------------------------------------------------------------------------
AGCC_PlayerCharacter::AGCC_PlayerCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	GetCapsuleComponent()->InitCapsuleSize(42.f, 96.f);
	
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->JumpZVelocity = 500.f;
	GetCharacterMovement()->AirControl = 0.35f;
	GetCharacterMovement()->MaxWalkSpeed = 500.f;
	GetCharacterMovement()->MinAnalogWalkSpeed = 20.f;
	GetCharacterMovement()->BrakingDecelerationWalking = 2000.f;
	GetCharacterMovement()->BrakingDecelerationFalling = 2000.f;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraBoom");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f;
	CameraBoom->bUsePawnControlRotation = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

//----------------------------------------------------------------------------------------------------------------------
UAbilitySystemComponent* AGCC_PlayerCharacter::GetAbilitySystemComponent() const
{
	AGCC_PlayerState* GCC_PlayerState = Cast<AGCC_PlayerState>(GetPlayerState());
	if (!IsValid(GCC_PlayerState))
	{
		return nullptr;
	}
	
	return GCC_PlayerState->GetAbilitySystemComponent();
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_PlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if(!IsValid(GetAbilitySystemComponent()) || !HasAuthority())
	{
		return;
	}
	
	// We set the Owner Actor and the Avatar Actor
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
	GiveStartupAbilities();
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_PlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if(!IsValid(GetAbilitySystemComponent()))
	{
		return;
	}
	
	// We set the Owner Actor and the Avatar Actor
	GetAbilitySystemComponent()->InitAbilityActorInfo(GetPlayerState(), this);
}
