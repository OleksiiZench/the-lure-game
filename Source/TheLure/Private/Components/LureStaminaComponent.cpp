// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.


#include "Components/LureStaminaComponent.h"

#include "LureDebugHelper.h"

void ULureStaminaComponent::SetStamina(bool bIsSprint)
{
	if (bIsSprint)
		Debug::Print(TEXT("On Stamina"));
	else
		Debug::Print(TEXT("Off Stamina"));
}
