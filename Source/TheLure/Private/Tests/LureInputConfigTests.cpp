// Copyright 2026 Oleksii Zenchenko & Denys Honcherenko. All Rights Reserved.

#include "Misc/AutomationTest.h"

#if WITH_DEV_AUTOMATION_TESTS

#include "DataAssets/LureInputConfig.h"
#include "InputAction.h"
#include "LureGameplayTags.h"




IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLureInputConfig_FindsRegisteredAction,
	"TheLure.InputConfig.FindsRegisteredAction",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FLureInputConfig_FindsRegisteredAction::RunTest(const FString& Parameters)
{
	// Arrange
	ULureInputConfig* InputConfig = NewObject<ULureInputConfig>();
	UInputAction *MoveAction = NewObject<UInputAction>();
	
	FLureInputAction Entry;
	Entry.InputAction = MoveAction;
	Entry.InputTag = LureGameplayTags::InputTag_Move;
	InputConfig->NativeInputActions.Add(Entry);
	
	// Act
	const UInputAction* FoundAction = InputConfig->FindNativeInputActionForTag(LureGameplayTags::InputTag_Move);
	
	// Assert
	TestTrue(
		TEXT("The method must return exectly the InputAction that is registered under this tag"),
		FoundAction == MoveAction
	);
	
	return true;
}




IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLureInputConfig_ReturnsNullForUnknownTag,
	"TheLure.InputConfig.ReturnsNullForUnknownTag",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FLureInputConfig_ReturnsNullForUnknownTag::RunTest(const FString& Parameters)
{
	// Arrange
	ULureInputConfig* InputConfig = NewObject<ULureInputConfig>();
	UInputAction *MoveAction = NewObject<UInputAction>();
	
	FLureInputAction Entry;
	Entry.InputAction = MoveAction;
	Entry.InputTag = LureGameplayTags::InputTag_Move;
	InputConfig->NativeInputActions.Add(Entry);
	
	// Act
	const UInputAction* FoundAction = InputConfig->FindNativeInputActionForTag(LureGameplayTags::InputTag_Look);
	
	// Assert
	TestNull(
		TEXT("No one has registered the Look tag  the result - should be nullptr"),
		FoundAction
	);
	
	return true;
}




IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLureInputConfig_SkipsEntryWithNullAction,
	"TheLure.InputConfig.SkipsEntryWithNullAction",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FLureInputConfig_SkipsEntryWithNullAction::RunTest(const FString& Parameters)
{
	// Arrange
	ULureInputConfig* InputConfig = NewObject<ULureInputConfig>();
	
	FLureInputAction BrokenEntry;
	BrokenEntry.InputAction = nullptr;
	BrokenEntry.InputTag = LureGameplayTags::InputTag_Move;
	InputConfig->NativeInputActions.Add(BrokenEntry);
	
	// Act
	const UInputAction* FoundAction = InputConfig->FindNativeInputActionForTag(LureGameplayTags::InputTag_Move);
	
	// Assert
	TestNull(
		TEXT("Even if the tag matches, a record with InputAction == nullptr should not be returned"),
		FoundAction
	);
	
	return true;
}




IMPLEMENT_SIMPLE_AUTOMATION_TEST(
	FLureInputConfig_ReturnsCorrectActionAmongMultiple,
	"TheLure.InputConfig.ReturnsCorrectActionAmongMultiple",
	EAutomationTestFlags::EditorContext | EAutomationTestFlags::ProductFilter)

bool FLureInputConfig_ReturnsCorrectActionAmongMultiple::RunTest(const FString& Parameters)
{
	// Arrange
	ULureInputConfig* InputConfig = NewObject<ULureInputConfig>();
	UInputAction *MoveAction = NewObject<UInputAction>();
	UInputAction *LookAction = NewObject<UInputAction>();
	
	FLureInputAction MoveEntry;
	MoveEntry.InputAction = MoveAction;
	MoveEntry.InputTag = LureGameplayTags::InputTag_Move;
	
	FLureInputAction LookEntry;
	LookEntry.InputAction = LookAction;
	LookEntry.InputTag = LureGameplayTags::InputTag_Look;
	
	InputConfig->NativeInputActions.Add(MoveEntry);
	InputConfig->NativeInputActions.Add(LookEntry);
	
	// Act
	const UInputAction* FoundMoveAction = InputConfig->FindNativeInputActionForTag(LureGameplayTags::InputTag_Move);
	const UInputAction* FoundLookAction = InputConfig->FindNativeInputActionForTag(LureGameplayTags::InputTag_Look);
	
	// Assert
	TestTrue(
		TEXT("The Move tag must return MoveAction specifically"),
		FoundMoveAction == MoveAction
	);
	
	TestTrue(
		TEXT("The Move tag must return LookAction specifically, not MoveAction"),
		FoundLookAction == LookAction
	);
	
	return true;
}

#endif
