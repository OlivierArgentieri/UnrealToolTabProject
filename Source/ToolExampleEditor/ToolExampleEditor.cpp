#include "ToolExampleEditor.h"
#include "Modules/ModuleManager.h"
#include "LevelEditor.h"
#include "MenuTool/MenuTool.h"
#include "TabTool/TabTool.h"

IMPLEMENT_GAME_MODULE(FToolExampleEditor, ToolExampleEditor)

TSharedRef<FWorkspaceItem> FToolExampleEditor::MenuRoot = FWorkspaceItem::NewGroup(FText::FromString("Menu Root"));

void FToolExampleEditor::AddModuleListeners()
{
	ModuleListeners.Add(MakeShareable(new MenuTool));
	ModuleListeners.Add(MakeShareable(new TabTool));
}

void FToolExampleEditor::AddMenuExtension(const FMenuExtensionDelegate& _extensionDelegate, FName _extensionHook,
	const TSharedPtr<FUICommandList>& _commandList, EExtensionHook::Position _position)
{
	MenuExtender->AddMenuExtension(_extensionHook, _position, _commandList, _extensionDelegate);
}


void FToolExampleEditor::MakePullDownMenu(FMenuBarBuilder& _menuBuilder)
{
	_menuBuilder.AddPullDownMenu
	(
		FText::FromString("Example"),
		FText::FromString("Open the Example Menu"),
		FNewMenuDelegate::CreateRaw(this, &FToolExampleEditor::FillPullDownMenu),
		"Example",
		FName(TEXT("ËxampleMenu"))
	);
}

void FToolExampleEditor::FillPullDownMenu(FMenuBuilder& _menuBuilder)
{
	// 2 empty sections
	_menuBuilder.BeginSection("ExampleSection", FText::FromString("Section 1"));
	_menuBuilder.AddMenuSeparator(FName("Section_1"));
	_menuBuilder.EndSection();

	_menuBuilder.BeginSection("ExampleSection", FText::FromString("Section 2"));
	_menuBuilder.AddMenuSeparator(FName("Section_2"));
	_menuBuilder.EndSection();
}

void FToolExampleEditor::StartupModule()
{
	if (IsRunningCommandlet()) return;

	FLevelEditorModule& _levelEditorModule = FModuleManager::LoadModuleChecked<FLevelEditorModule>("LevelEditor");
	LevelEditorMenuExtensibilityManager = _levelEditorModule.GetMenuExtensibilityManager();
	MenuExtender = MakeShareable(new FExtender);
	MenuExtender->AddMenuBarExtension
		(
		"Window",
		EExtensionHook::After, 
		NULL,
		FMenuBarExtensionDelegate::CreateRaw(this, &FToolExampleEditor::MakePullDownMenu)
		);
	LevelEditorMenuExtensibilityManager->AddExtender(MenuExtender);

	// call mother method
	IExampleModuleInterface::StartupModule();

	//FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("hey"));
}

void FToolExampleEditor::ShutdownModule()
{

}
