// Copyright Epic Games, Inc. All Rights Reserved.

#include "AudioRuntimeListStyle.h"
#include "AudioRuntimeList.h"
#include "Framework/Application/SlateApplication.h"
#include "Styling/SlateStyleRegistry.h"
#include "Slate/SlateGameResources.h"
#include "Interfaces/IPluginManager.h"
#include "Styling/SlateStyleMacros.h"
#include "Sound/SoundWave.h"

#define RootToContentDir Style->RootToContentDir

TSharedPtr<FSlateStyleSet> FAudioRuntimeListStyle::StyleInstance = nullptr;

void FAudioRuntimeListStyle::Initialize()
{
	if (!StyleInstance.IsValid())
	{
		StyleInstance = Create();
		FSlateStyleRegistry::RegisterSlateStyle(*StyleInstance);
	}
}

void FAudioRuntimeListStyle::Shutdown()
{
	FSlateStyleRegistry::UnRegisterSlateStyle(*StyleInstance);
	ensure(StyleInstance.IsUnique());
	StyleInstance.Reset();
}

FName FAudioRuntimeListStyle::GetStyleSetName()
{
	static FName StyleSetName(TEXT("AudioRuntimeListStyle"));
	return StyleSetName;
}


const FVector2D Icon16x16(16.0f, 16.0f);
const FVector2D Icon20x20(20.0f, 20.0f);

TSharedRef< FSlateStyleSet > FAudioRuntimeListStyle::Create()
{
	TSharedRef< FSlateStyleSet > Style = MakeShareable(new FSlateStyleSet("AudioRuntimeListStyle"));
	Style->SetContentRoot(IPluginManager::Get().FindPlugin("AudioRuntimeList")->GetBaseDir() / TEXT("Resources"));

	Style->Set("AudioRuntimeList.PluginAction", new IMAGE_BRUSH(TEXT("SoundIcon"), Icon20x20));
	return Style;
}

void FAudioRuntimeListStyle::ReloadTextures()
{
	if (FSlateApplication::IsInitialized())
	{
		FSlateApplication::Get().GetRenderer()->ReloadTextureResources();
	}
}

const ISlateStyle& FAudioRuntimeListStyle::Get()
{
	return *StyleInstance;
}
