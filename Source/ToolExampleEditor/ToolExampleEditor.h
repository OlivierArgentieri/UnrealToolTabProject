#pragma once


#include "IExampleModuleInterface.h"
#include "Modules/ModuleManager.h"

class FToolExampleEditor : public IExampleModuleInterface
{
protected:
	// attr
	TSharedPtr<FExtensibilityManager> LevelEditorMenuExtensibilityManager;
	TSharedPtr<FExtender> MenuExtender;

	static TSharedRef<FWorkspaceItem> MenuRoot;

	// method
	void MakePullDownMenu(FMenuBarBuilder& _menuBuilder);
	void FillPullDownMenu(FMenuBuilder& _menuBuilder);
	
public:

	/* IModuleInterface implementation */
	virtual void StartupModule() override;
	virtual void ShutdownModule() override;

	virtual void AddModuleListeners() override;

	// method
	static FToolExampleEditor& Get()
	{
		return FModuleManager::LoadModuleChecked<FToolExampleEditor>("ToolExampleEditor");
	}
	
	static bool IsAvailable()
	{
		return FModuleManager::Get().IsModuleLoaded("ToolExampleEditor");
	}

	void AddMenuExtension(const FMenuExtensionDelegate& _extensionDelegate, FName _extensionHook, const TSharedPtr<FUICommandList>& _commandList = NULL, EExtensionHook::Position _position = EExtensionHook::Before);
	TSharedRef<FWorkspaceItem> GetMenuRoot() { return MenuRoot; }
};
