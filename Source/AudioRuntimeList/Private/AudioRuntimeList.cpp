// Copyright Epic Games, Inc. All Rights Reserved.

#include "AudioRuntimeList.h"
#include "AudioRuntimeListStyle.h"
#include "AudioRuntimeListCommands.h"
#include "Misc/MessageDialog.h"
#include "ToolMenus.h"
#include "Sound/SoundWave.h"
#include "Sound/SoundCue.h"
#include "Editor/ContentBrowser/Public/ContentBrowserModule.h"
#include "Editor/ContentBrowser/Private/SContentBrowser.h"
#include "AssetRegistry/AssetRegistryModule.h"

static const FName AudioRuntimeListTabName("AudioRuntimeList");

#define LOCTEXT_NAMESPACE "FAudioRuntimeListModule"

void FAudioRuntimeListModule::StartupModule()
{
	// This code will execute after your module is loaded into memory; the exact timing is specified in the .uplugin file per-module
	
	FAudioRuntimeListStyle::Initialize();
	FAudioRuntimeListStyle::ReloadTextures();

	FAudioRuntimeListCommands::Register();
	
	PluginCommands = MakeShareable(new FUICommandList);

	PluginCommands->MapAction(
		FAudioRuntimeListCommands::Get().PluginAction,
		FExecuteAction::CreateRaw(this, &FAudioRuntimeListModule::PluginButtonClicked),
		FCanExecuteAction());

	UToolMenus::RegisterStartupCallback(FSimpleMulticastDelegate::FDelegate::CreateRaw(this, &FAudioRuntimeListModule::RegisterMenus));
}

void FAudioRuntimeListModule::ShutdownModule()
{
	// This function may be called during shutdown to clean up your module.  For modules that support dynamic reloading,
	// we call this function before unloading the module.

	UToolMenus::UnRegisterStartupCallback(this);

	UToolMenus::UnregisterOwner(this);

	FAudioRuntimeListStyle::Shutdown();

	FAudioRuntimeListCommands::Unregister();
}

void FAudioRuntimeListModule::PluginButtonClicked()
{
	// Put your "OnButtonClicked" stuff here
	
	float currentDuration = 0.f;
	TArray<FAssetIdentifier> ReferencedObjects;
	TArray<FAssetData> SelectedAssetDatas;
	TArray<USoundWave*> SelectedSounds; 
	int modSec;
	int modMin;
	int modHr;
	int referenceSoundCues = 0;
	bool bReferencesCue = false;

	

	FContentBrowserModule& ContentBrowser = FModuleManager::LoadModuleChecked<FContentBrowserModule>("ContentBrowser");
	ContentBrowser.Get().GetSelectedAssets(SelectedAssetDatas);

	FAssetRegistryModule& AssetRegistry = FModuleManager::GetModuleChecked<FAssetRegistryModule>("AssetRegistry");
	
	//FReferenceFinder ObjectReferenceCollector(ReferencedObjects);//, obj,false,true,true,false);
	for (FAssetData data : SelectedAssetDatas)
	{
		if (Cast<USoundWave>(data.GetAsset()))
		{
			SelectedSounds.Add(Cast<USoundWave>(data.GetAsset()));
			currentDuration += Cast<USoundWave>(data.GetAsset())->Duration; 
			
			/*
			AssetRegistry.Get().GetDependencies(data.PackageName, ReferencedObjects, EAssetRegistryDependencyType::All);

			ReferencedObjects.Empty();
			UObject* obj = data.GetAsset();
			//TArray<FReferencerInformation>* references;
			//obj->RetrieveReferencers(nullptr, references);
			
			//ObjectReferenceCollector.FindReferences(obj);
			UE_LOG(LogTemp, Warning, TEXT("Referenced Objects : %s"), )

			for (FAssetIdentifier ref : ReferencedObjects)
			{
				FString refname = ref.PrimaryAssetType.GetName().ToString();
				UE_LOG(LogTemp, Warning, TEXT("Referenced Objects : %s"), *FString(refname));
				if (ref.PrimaryAssetType.GetName().ToString() == "")
				{
					referenceSoundCues += 1;
					break;
				}
			}
			/**/
		}
	}
	
	
	

	modSec = int(currentDuration) % 60;
	modMin = int(currentDuration / 60) % 60;
	modHr = int(currentDuration / 3600);

	FString SecString = modSec > 9 ? FString::FromInt(modSec) : "0" + FString::FromInt(modSec);
	FString MinString = modMin > 9 ? FString::FromInt(modMin) : "0" + FString::FromInt(modMin);
	FString HrString = FString::FromInt(modHr);

	FText DialogText = FText::Format(
		FText::FromString("The selected {0} sounds have a total runtime of:\n{1}:{2}:{3}\nOr {4} total seconds"),// \n\n{ 5 } Sound Wavs do not have a Sound Cue referenced."),
		FText::FromString(FString::FromInt(SelectedSounds.Num())),
		FText::FromString(HrString),
		FText::FromString(MinString),
		FText::FromString(SecString),
		FText::FromString(FString::FromInt(currentDuration)),
		FText::FromString(FString::FromInt(SelectedSounds.Num() - referenceSoundCues))
	);
	FMessageDialog::Open(EAppMsgType::Ok, DialogText);
}

void FAudioRuntimeListModule::RegisterMenus()
{
	// Owner will be used for cleanup in call to UToolMenus::UnregisterOwner
	FToolMenuOwnerScoped OwnerScoped(this);

	{
		UToolMenu* Menu = UToolMenus::Get()->ExtendMenu("LevelEditor.MainMenu.Window");
		{
			FToolMenuSection& Section = Menu->FindOrAddSection("WindowLayout");
			Section.AddMenuEntryWithCommandList(FAudioRuntimeListCommands::Get().PluginAction, PluginCommands);
		}
	}

	{
		UToolMenu* ToolbarMenu = UToolMenus::Get()->ExtendMenu("LevelEditor.LevelEditorToolBar.PlayToolBar");
		{
			FToolMenuSection& Section = ToolbarMenu->FindOrAddSection("PluginTools");
			{
				FToolMenuEntry& Entry = Section.AddEntry(FToolMenuEntry::InitToolBarButton(FAudioRuntimeListCommands::Get().PluginAction));
				Entry.SetCommandList(PluginCommands);
			}
		}
	}
}

#undef LOCTEXT_NAMESPACE
	
IMPLEMENT_MODULE(FAudioRuntimeListModule, AudioRuntimeList)