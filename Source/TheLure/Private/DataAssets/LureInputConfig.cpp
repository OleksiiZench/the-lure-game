// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.


#include "DataAssets/LureInputConfig.h"

#include "LureDebugHelper.h"

const UInputAction* ULureInputConfig::FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound) const
{
	for (const FLureInputAction	&Action : NativeInputActions)
	{
		if (Action.InputAction && Action.InputTag == InputTag)
		{
			return Action.InputAction;
		}
	}
	
	if (bLogNotFound)
		Debug::PrintError(FString::Printf(TEXT("Can't find NativeInputAction for InputTag [%s] on InputConfig [%s]."), *InputTag.ToString(), *GetNameSafe(this)));
	
	return nullptr;
}
