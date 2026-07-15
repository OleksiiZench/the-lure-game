// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"

#include "LureStaminaComponent.generated.h"


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class THELURE_API ULureStaminaComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	void SetStamina(bool bIsSprint);
};
