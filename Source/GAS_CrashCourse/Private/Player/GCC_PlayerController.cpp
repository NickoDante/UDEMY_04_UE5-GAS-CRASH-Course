// Nicolas Nieto - GCC - Copyright - 2026

// Header include
#include "GAS_CrashCourse/Public/Player/GCC_PlayerController.h"

// Engine Includes
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/Character.h"

//----------------------------------------------------------------------------------------------------------------------
void AGCC_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	// There are 3 ways to validate 
	/* OPTION 1
	 * UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	 * if (IsValid(InputSubsystem)) */
	
	/* OPTION 2
	 * 	if (UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()); IsValid(InputSubsystem)) */
	
	// OPTION 3
	
	UEnhancedInputLocalPlayerSubsystem* InputSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputSubsystem))
	{
		return;
	}
	
	for (UInputMappingContext* Context : InputMappingContexts)
	{
		InputSubsystem->AddMappingContext(Context, 0);
	}
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent))
	{
		return;
	}
	
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Started, this, &ThisClass::Jump);
	EnhancedInputComponent->BindAction(JumpAction, ETriggerEvent::Completed, this, &ThisClass::StopJumping);
	
	EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ThisClass::Move);
	
	EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ThisClass::Look);
	
	EnhancedInputComponent->BindAction(PrimaryAction, ETriggerEvent::Started, this, &ThisClass::PrimaryAbility);
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_PlayerController::Jump()
{
	if (!IsValid(GetCharacter()))
	{
		return;
	}
	
	GetCharacter()->Jump();
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_PlayerController::StopJumping()
{
	if (!IsValid(GetCharacter()))
	{
		return;
	}
	
	GetCharacter()->StopJumping();
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_PlayerController::Move(const FInputActionValue& Value)
{
	if (!IsValid(GetPawn()))
	{
		return;
	}
	
	const FVector2D MovementVector = Value.Get<FVector2D>();
	
	// Find which way is forward
	const FRotator YawRotation(0.f, GetControlRotation().Yaw, 0.f);
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
	GetPawn()->AddMovementInput(ForwardDirection, MovementVector.Y);
	GetPawn()->AddMovementInput(RightDirection, MovementVector.X);
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_PlayerController::Look(const FInputActionValue& Value)
{
	const FVector2D LookAxisVector = Value.Get<FVector2D>();
	
	AddYawInput(LookAxisVector.X);
	AddPitchInput(LookAxisVector.Y);
}

//----------------------------------------------------------------------------------------------------------------------
void AGCC_PlayerController::PrimaryAbility()
{
	GEngine->AddOnScreenDebugMessage(1, 5.f, FColor::Green, TEXT("Primary Ability"));
}
