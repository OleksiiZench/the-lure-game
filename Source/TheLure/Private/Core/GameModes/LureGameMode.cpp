// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.


#include "Core/GameModes/LureGameMode.h"

#include "Player/LurePlayerCharacter.h"
#include "Player/LurePlayerController.h"
#include "Core/LureGameState.h"

ALureGameMode::ALureGameMode()
{
	DefaultPawnClass = ALurePlayerCharacter::StaticClass();
	PlayerControllerClass = ALurePlayerController::StaticClass();
	GameStateClass = ALureGameState::StaticClass();
}
