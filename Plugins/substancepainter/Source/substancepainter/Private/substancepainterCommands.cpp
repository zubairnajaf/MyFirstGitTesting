// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "substancepainterCommands.h"

#define LOCTEXT_NAMESPACE "FsubstancepainterModule"

void FsubstancepainterCommands::RegisterCommands()
{
	UI_COMMAND(OpenPluginWindow, "substancepainter", "Bring up substancepainter window", EUserInterfaceActionType::Button, FInputGesture());
}

#undef LOCTEXT_NAMESPACE
