// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Characters/LureBaseCharacter.h"

#include "LurePlayerCharacter.generated.h"

class UCameraComponent;
class ULureInputConfig;
class ULureStaminaComponent;

struct FInputActionValue;

/**
 * 
 */
UCLASS()
class THELURE_API ALurePlayerCharacter : public ALureBaseCharacter
{
	GENERATED_BODY()
	
public:
	ALurePlayerCharacter();
	
	virtual void SetupPlayerInputComponent(UInputComponent *PlayerInputComponent) override;
	
private:
#pragma region Inputs
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lure|Input", meta = (AllowPrivateAccess = "true"))
	ULureInputConfig *InputConfig;
	
	void Input_Move(const FInputActionValue &InputActionValue);
	void Input_Look(const FInputActionValue &InputActionValue);
	void Input_SprintStarted(const FInputActionValue &InputActionValue);
	void Input_SprintCompleted(const FInputActionValue &InputActionValue);
#pragma endregion
	
#pragma region Components
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lure|Components", meta = (AllowPrivateAccess = "true"))
	UCameraComponent *CameraComponent;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Lure|Components", meta = (AllowPrivateAccess = "true"))
	ULureStaminaComponent *StaminaComponent;
#pragma endregion
	
	void SetupComponents();
	void SetupCamera();
	void SetupStaminaComponent();
};
