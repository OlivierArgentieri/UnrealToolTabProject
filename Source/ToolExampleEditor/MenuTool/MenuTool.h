#include "ToolExampleEditor/IExampleModuleInterface.h"
#include "Framework/MultiBox/MultiBoxBuilder.h"

class MenuTool : public IExampleModuleListenerInterface, public TSharedFromThis<MenuTool>
{
public:
	virtual ~MenuTool() {}

	virtual void OnStartupModule() override;
	virtual void OnShutdownModule() override;

	void MakeMenuEntry(FMenuBuilder& _menuBuilder);

protected:
	TSharedPtr<FUICommandList> CommandList;

	void MapCommands();

	// UI Command functions
	void MenuCommand1();
	void MenuCommand2();
	void MenuCommand3();

	// SubMenu
	void MakeSubMenu(FMenuBuilder& _menuBuilder);

	// custom widget
	FName TagToAdd;
	FReply AddTag();
	FText GetTagToAddText() const;
	void OnTagToAddTextCommited(const FText& _inText, ETextCommit::Type _commitInfo);
	
};
