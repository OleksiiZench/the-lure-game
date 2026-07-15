// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.


#include "Player/LurePlayerCharacter.h"

#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "EnhancedInputComponent.h"

#include "DataAssets/LureInputConfig.h"
#include "LureGameplayTags.h"
#include "Components/LureStaminaComponent.h"

ALurePlayerCharacter::ALurePlayerCharacter()
{
	SetupComponents();
}

void ALurePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	if (UEnhancedInputComponent *EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (!InputConfig)
			return;
		
		const UInputAction *MoveAction = InputConfig->FindNativeInputActionForTag(LureGameplayTags::InputTag_Move, true);
		if (MoveAction)
			EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ALurePlayerCharacter::Input_Move);
		
		const UInputAction *LookAction = InputConfig->FindNativeInputActionForTag(LureGameplayTags::InputTag_Look, true);
		if (LookAction)
			EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ALurePlayerCharacter::Input_Look);
		
		const UInputAction *SprintAction = InputConfig->FindNativeInputActionForTag(LureGameplayTags::InputTag_Sprint, true);
		if (SprintAction)
		{
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Started, this, &ALurePlayerCharacter::Input_SprintStarted);
			EnhancedInputComponent->BindAction(SprintAction, ETriggerEvent::Completed, this, &ALurePlayerCharacter::Input_SprintCompleted);
		}
	}
}

void ALurePlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	if (Controller)
	{
		AddMovementInput(GetActorForwardVector(), MovementVector.Y);
		AddMovementInput(GetActorRightVector(), MovementVector.X);
	}
}

void ALurePlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();
	if (Controller)
	{
		AddControllerYawInput(LookAxisVector.X);
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void ALurePlayerCharacter::Input_SprintStarted(const FInputActionValue& InputActionValue)
{
	StaminaComponent->SetSprint(true);
}

void ALurePlayerCharacter::Input_SprintCompleted(const FInputActionValue& InputActionValue)
{
	StaminaComponent->SetSprint(false);
}

void ALurePlayerCharacter::SetupComponents()
{
	SetupCamera();
	SetupStaminaComponent();
}

void ALurePlayerCharacter::SetupCamera()
{
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetCapsuleComponent());
	CameraComponent->SetRelativeLocation(FVector(-10.0f, 0.0f, 60.0f));
	CameraComponent->bUsePawnControlRotation = true;
}

void ALurePlayerCharacter::SetupStaminaComponent()
{
	StaminaComponent = CreateDefaultSubobject<ULureStaminaComponent>(TEXT("StaminaComponent"));
}
