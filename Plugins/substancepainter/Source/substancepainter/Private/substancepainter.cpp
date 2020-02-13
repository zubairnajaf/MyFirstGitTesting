// Copyright 1998-2019 Epic Games, Inc. All Rights Reserved.

#include "substancepainter.h"
#include "substancepainterStyle.h"
#include "substancepainterCommands.h"
#include "LevelEditor.h"
#include "Widgets/Docking/SDockTab.h"
#include "Widgets/Layout/SBox.h"
#include "Widgets/Text/STextBlock.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

static const FName substancepainterTabName("substancepainter");

#define LOCTEXT_NAMESPACE "FsubstancepainterModule"

void FsubstancepainterModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FsubstancepainterStyle::Initialize();
	FsubstancepainterStyle::ReloadTextures();

	FsubstancepainterCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FsubstancepainterCommands::Get().OpenPluginWindow,
		FExecuteAction::CreateRaw(this, &FsubstancepainterModule::PluginButtonClicked),
		FCanExecuteAction());
		
	FLevelEditorModule& LevelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	
	{
		TSharedPtr<FExtender> MenuExtender = MakeShareable(new FExtender());
		MenuExtender->AddMenuExtension("WindowLayout", EExtensionHook::After, PluginCommands, FMenuExtensionDelegate::CreateRaw(this, &FsubstancepainterModule::AddMenuExtension));

		LevelEditorModule.GetMenuExtensibilityManager()->AddExtender(MenuExtender);
	}
	
	{
		TSharedPtr<FExtender> ToolbarExtender = MakeShareable(new FExtender);
		ToolbarExtender->AddToolBarExtension("Settings", EExtensionHook::After, PluginCommands, FToolBarExtensionDelegate::CreateRaw(this, &FsubstancepainterModule::AddToolbarExtension));
		
		LevelEditorModule.GetToolBarExtensibilityManager()->AddExtender(ToolbarExtender);
	}
	
	FGlobalTabmanager::Get()->RegisterNomadTabSpawner(substancepainterTabName, FOnSpawnTab::CreateRaw(this, &FsubstancepainterModule::OnSpawnPluginTab))
		.SetDisplayName(LOCTEXT("FsubstancepainterTabTitle", "substancepainter"))
		.SetMenuType(ETabSpawnerMenuType::Hidden);
}

void FsubstancepainterModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.
	FsubstancepainterStyle::Shutdown();

	FsubstancepainterCommands::Unregister();

	FGlobalTabmanager::Get()->UnregisterNomadTabSpawner(substancepainterTabName);
}

TSharedRef<SDockTab> FsubstancepainterModule::OnSpawnPluginTab(const FSpawnTabArgs& SpawnTabArgs)
{
	FText WidgetText = FText::Format(
		LOCTEXT("WindowWidgetText", "Add code to {0} in {1} to override this window's contents"),
		FText::FromString(TEXT("FsubstancepainterModule::OnSpawnPluginTab")),
		FText::FromString(TEXT("substancepainter.cpp"))
		);

	return SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			// Put your tab content here!
			SNew(SBox)
			.HAlign(HAlign_Center)
			.VAlign(VAlign_Center)
			[
				SNew(STextBlock)
				.Text(WidgetText)
			]
		];
}

void FsubstancepainterModule::PluginButtonClicked()
{
	FGlobalTabmanager::Get()->InvokeTab(substancepainterTabName);
}

void FsubstancepainterModule::AddMenuExtension(FMenuBuilder& Builder)
{
	Builder.AddMenuEntry(FsubstancepainterCommands::Get().OpenPluginWindow);
}

void FsubstancepainterModule::AddToolbarExtension(FToolBarBuilder& Builder)
{
	Builder.AddToolBarButton(FsubstancepainterCommands::Get().OpenPluginWindow);
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FsubstancepainterModule, substancepainter)