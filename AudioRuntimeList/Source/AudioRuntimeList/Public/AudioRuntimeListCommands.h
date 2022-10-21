// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "AudioRuntimeListStyle.h"

class FAudioRuntimeListCommands : public TCommands<FAudioRuntimeListCommands>
{
public:

	FAudioRuntimeListCommands()
		: TCommands<FAudioRuntimeListCommands>(TEXT("AudioRuntimeList"), NSLOCTEXT("Contexts", "AudioRuntimeList", "AudioRuntimeList Plugin"), NAME_None, FAudioRuntimeListStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > PluginAction;
};
