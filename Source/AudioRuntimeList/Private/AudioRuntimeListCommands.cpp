// Copyright Epic Games, Inc. All Rights Reserved.

#include "AudioRuntimeListCommands.h"

#define LOCTEXT_NAMESPACE "FAudioRuntimeListModule"

void FAudioRuntimeListCommands::RegisterCommands()
{
	UI_COMMAND(PluginAction, "AudioRuntimeList", "Check Selected SoundWav Total Duration", EUserInterfaceActionType::Button, FInputChord());
}

#undef LOCTEXT_NAMESPACE
