// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

#include "Engine/World.h"

#include "Player/LurePlayerCharacter.h"
#include "Components/LureStaminaComponent.h"
#include "GameFramework/CharacterMovementComponent.h"


IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLureStamina_DrainAndRegen,
	"TheLure.Stamina.DrainAndRegen",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FLureStamina_DrainAndRegen::RunTest(const FString& Parameters)
{
	// Arrange (Preparing environment)
	UWorld *TestWorld = UWorld::CreateWorld(EWorldType::Game, false);
	
	ALurePlayerCharacter *PlayerCharacter = TestWorld->SpawnActor<ALurePlayerCharacter>();
	ULureStaminaComponent *StaminaComp = PlayerCharacter->FindComponentByClass<ULureStaminaComponent>();
	UCharacterMovementComponent *MovementComp = PlayerCharacter->GetCharacterMovement();
	
	if (StaminaComp == nullptr || MovementComp == nullptr)
	{
		AddError(TEXT("Character failed to initialize Stamina or Movement component"));
		TestWorld->DestroyWorld(false);
		return false;
	}
	
	MovementComp->MaxWalkSpeed = 500.0f;
	
	StaminaComp->BeginPlay();
	
	// Arrange
	MovementComp->Velocity = PlayerCharacter->GetActorForwardVector() * 500.0f;
	StaminaComp->SetSprint(true);
	float InitialStamina = StaminaComp->GetCurrentStamina();
	
	// Act
	StaminaComp->UpdateStamina(1.0f);
	
	// Assert
	TestTrue(
		TEXT("Stamina should decrease when sprinting and moving forward"),
		StaminaComp->GetCurrentStamina() < InitialStamina
	);
	TestTrue(
		TEXT("Character should move at sprint speed"),
		MovementComp->MaxWalkSpeed > 500.0f
	);
	
	
	// Act
	StaminaComp->UpdateStamina(10.0f);
	
	// Assert
	TestEqual(
		TEXT("Stamina should not drop below 0"),
		StaminaComp->GetCurrentStamina(), 
		0.0f
	);
	TestFalse(
		TEXT("Sprint should automatically turn off when stamina hits 0"),
		StaminaComp->IsSprinting()
	);
	TestEqual(
		TEXT("Speed should revert to walk speed after exhaustion"),
		MovementComp->MaxWalkSpeed,
		500.0f
	);
	
	
	// Arrange
	MovementComp->Velocity = FVector::ZeroVector;
	
	// Act
	StaminaComp->UpdateStamina(0.1f);
	MovementComp->Velocity = PlayerCharacter->GetActorForwardVector() * 500.0f;
	StaminaComp->SetSprint(true);
	
	// Assert
	TestFalse(
	TEXT("Stamina should be blocked if stamina is below the threshold"),
	StaminaComp->IsSprinting()
	);
	TestEqual(
		TEXT("Speed should remain at walk speed if threshold is not met"),
		MovementComp->MaxWalkSpeed,
		500.0f
	);
	
	
	// Arrange
	MovementComp->Velocity = FVector::ZeroVector;
	
	// Act
	StaminaComp->UpdateStamina(1.0f);
	MovementComp->Velocity = PlayerCharacter->GetActorForwardVector() * 500.0f;
	StaminaComp->SetSprint(true);
	
	// Assert
	TestTrue(
	TEXT("Sprint should activate when stamina is above the threshold"),
	StaminaComp->IsSprinting()
	);
	TestTrue(
		TEXT("Speed should change to sprint speed"),
		MovementComp->MaxWalkSpeed > 500.0f
	);
	
	
	TestWorld->DestroyWorld(false);
	
	return true;
}

#endif
