// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.


#include "Player/LurePlayerController.h"

#include "EnhancedInputSubsystems.h"
#include "Engine/LocalPlayer.h"

void ALurePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	AddDefaultMappingContext();
}

void ALurePlayerController::AddDefaultMappingContext()
{
	if (UEnhancedInputLocalPlayerSubsystem *Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		if (DefaultMappingContext)
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
	}
}
