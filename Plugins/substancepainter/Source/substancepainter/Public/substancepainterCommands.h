// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Framework/Commands/Commands.h"
#include "substancepainterStyle.h"

class FsubstancepainterCommands : public TCommands<FsubstancepainterCommands>
{
public:

	FsubstancepainterCommands()
		: TCommands<FsubstancepainterCommands>(TEXT("substancepainter"), NSLOCTEXT("Contexts", "substancepainter", "substancepainter Plugin"), NAME_None, FsubstancepainterStyle::GetStyleSetName())
	{
	}

	// TCommands<> interface
	virtual void RegisterCommands() override;

public:
	TSharedPtr< FUICommandInfo > OpenPluginWindow;
};