// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.


#include "Components/LureStaminaComponent.h"

#include "GameFramework/CharacterMovementComponent.h"

#include "Player/LurePlayerCharacter.h"

ULureStaminaComponent::ULureStaminaComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void ULureStaminaComponent::BeginPlay()
{
	Super::BeginPlay();
	
	CachePlayerCharacter();
	CacheCharacterMovementComp();
}

void ULureStaminaComponent::TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UpdateStamina(DeltaTime);
}

void ULureStaminaComponent::SetSprint(bool bIsSprint)
{
	if (!CachedCharacterMovementComp)
		return;
	
	if (bIsSprint && IsMovingHorizontally())
	{
		CachedCharacterMovementComp->MaxWalkSpeed = SprintSpeed;
		bIsSprinting = true;
	}
	else
	{
		CachedCharacterMovementComp->MaxWalkSpeed = WalkSpeed;
		bIsSprinting = false;
	}
}

void ULureStaminaComponent::UpdateStamina(float DeltaTime)
{
	if (!CachedCharacterMovementComp)
		return;
	
	if (bIsSprinting)
	{
		bool bIsFalling = CachedCharacterMovementComp->IsFalling();
		
		if (!IsMovingHorizontally() || bIsFalling || IsMovingBackward())
		{
			SetSprint(false);
		}
		else
		{
			CurrentStamina -= StaminaDrainRate * DeltaTime;
		
			if (CurrentStamina <= 0.0f)
			{
				CurrentStamina = 0.0f;
				SetSprint(false);
			}
		}
	}
	else if (CurrentStamina < MaxStamina)
	{
		CurrentStamina += StaminaRegenRate * DeltaTime;
	}
}

bool ULureStaminaComponent::IsMovingHorizontally() const
{
	if (!CachedPlayerCharacter)
		return false;
	
	return !(CachedPlayerCharacter->GetVelocity().Size2D() < 5.0f);
}

bool ULureStaminaComponent::IsMovingBackward() const
{
	if (!CachedPlayerCharacter)
		return false;
	
	FVector Velocity = CachedPlayerCharacter->GetVelocity();
	
	if (Velocity.SizeSquared2D() < 10.0f)
	{
		return false;
	}
	
	FVector MovementDirection = Velocity.GetSafeNormal2D();
	FVector FacingDirection = CachedPlayerCharacter->GetActorForwardVector().GetSafeNormal2D();
	
	float DotProduct = FVector::DotProduct(MovementDirection, FacingDirection);
	
	return DotProduct < -0.1f;
}

void ULureStaminaComponent::CachePlayerCharacter()
{
	if (ALurePlayerCharacter *TempPlayer = Cast<ALurePlayerCharacter>(GetOwner()))
		CachedPlayerCharacter = TempPlayer;
}

void ULureStaminaComponent::CacheCharacterMovementComp()
{
	if (CachedPlayerCharacter)
	{
		CachedCharacterMovementComp = CachedPlayerCharacter->GetCharacterMovement();
	}
}
