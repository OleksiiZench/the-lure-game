// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"

#include "GameplayTagContainer.h"

#include "LureInputConfig.generated.h"

class UInputAction;

USTRUCT(BlueprintType)
struct FLureInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	const UInputAction *InputAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (Categories = "InputTag"))
	FGameplayTag InputTag;
};




UCLASS()
class THELURE_API ULureInputConfig : public UDataAsset
{
	GENERATED_BODY()
	
public:
	const UInputAction *FindNativeInputActionForTag(const FGameplayTag& InputTag, bool bLogNotFound = false) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Meta = (TitleProperty = "InputAction"))
	TArray<FLureInputAction> NativeInputActions;
};
