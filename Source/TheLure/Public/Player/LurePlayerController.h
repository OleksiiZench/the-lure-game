// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"

#include "LurePlayerController.generated.h"

class UCameraComponent;
class UInputMappingContext;

/**
 * 
 */
UCLASS()
class THELURE_API ALurePlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void SetupInputComponent() override;
	
private:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Lure|Input", meta = (AllowPrivateAccess = "true"))
	UInputMappingContext *DefaultMappingContext;
	
	void AddDefaultMappingContext();
};
