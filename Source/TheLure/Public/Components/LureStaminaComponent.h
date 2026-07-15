// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "LureStaminaComponent.generated.h"

class ALurePlayerCharacter;
class UCharacterMovementComponent;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELURE_API ULureStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	ULureStaminaComponent();
	
	virtual void BeginPlay() override;
	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;
	
	void SetSprint(bool bIsSprint);
	
private:
#pragma region SetupStamina
	UPROPERTY(EditDefaultsOnly, Category = "Lure|Movement")
	float WalkSpeed = 500.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Lure|Movement")
	float SprintSpeed = 800.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Lure|Movement")
	float MaxStamina = 3.0f;
	
	UPROPERTY(VisibleAnywhere, Category = "Lure|Movement")
	float CurrentStamina = MaxStamina;
	
	UPROPERTY(EditDefaultsOnly, Category = "Lure|Movement")
	float StaminaDrainRate = 1.0f;
	
	UPROPERTY(EditDefaultsOnly, Category = "Lure|Movement")
	float StaminaRegenRate = 1.0f;
#pragma endregion
	
	UPROPERTY()
	ALurePlayerCharacter *CachedPlayerCharacter;
	
	UPROPERTY()
	UCharacterMovementComponent *CachedCharacterMovementComp;
	
	bool bIsSprinting = false;
	
	void UpdateStamina(float DeltaTime);
	
	bool IsMovingHorizontally() const;
	bool IsMovingBackward() const;
	
	void CachePlayerCharacter();
	void CacheCharacterMovementComp();
};
