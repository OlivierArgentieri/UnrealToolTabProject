#include "TabTool.h"
#include "./WorldSetting/TabToolWorldSettings.h"


void TabTool::OnStartupModule()
{
	FExampleTabToolBase::OnStartupModule();
	FToolExampleEditor::Get().AddMenuExtension(FMenuExtensionDelegate::CreateRaw(this, &TabTool::MakeMenuEntry), FName("Section_2"));
}


void TabTool::OnShutdownModule()
{
	FExampleTabToolBase::OnShutdownModule();
}

void TabTool::Initialize()
{
	TabName = "TabTool";
	TabDisplayName = FText::FromString("Tab Tool");
	ToolTipText = FText::FromString("Tab Tool Window");
}

TSharedRef<SDockTab> TabTool::SpawnTab(const FSpawnTabArgs& _tabSpawnArgs)
{
	TSharedRef<SDockTab> _spawnedTab = SNew(SDockTab)
		.TabRole(ETabRole::NomadTab)
		[
			SNew(TabToolWorldSettings)
			.Tool(SharedThis(this))
		];
	
	return _spawnedTab;
}