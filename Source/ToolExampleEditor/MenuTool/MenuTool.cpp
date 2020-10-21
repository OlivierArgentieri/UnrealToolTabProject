#include "MenuTool.h"

#include "Engine/Selection.h"
#include "ToolExampleEditor/ToolExampleEditor.h"
#define LOCTEXT_NAMESPACE "MenuTool"

class MenuToolCommands : public TCommands<MenuToolCommands>
{
public:
	MenuToolCommands()
	: TCommands<MenuToolCommands>(
		TEXT("MenuTool"), // context name
		FText::FromString("Example Menu tool"), // context name for dipslaying
		NAME_None,
		FEditorStyle::GetStyleSetName() // Icon Style Set
		)
	{}

	virtual void RegisterCommands() override
	{
		UI_COMMAND(MenuCommand1, "Menu command 1", "Test Menu Command 1", EUserInterfaceActionType::Button, FInputGesture());
		UI_COMMAND(MenuCommand2, "Menu command 2", "Test Menu Command 2", EUserInterfaceActionType::Button, FInputGesture());
		UI_COMMAND(MenuCommand3, "Menu command 3", "Test Menu Command 3", EUserInterfaceActionType::Button, FInputGesture());
	}

public:
	TSharedPtr<FUICommandInfo> MenuCommand1;
	TSharedPtr<FUICommandInfo> MenuCommand2;
	TSharedPtr<FUICommandInfo> MenuCommand3;
	
};

void MenuTool::MapCommands()
{
	const auto& _commands = MenuToolCommands::Get();

	CommandList->MapAction
	(
		_commands.MenuCommand1,
		FExecuteAction::CreateSP(this, &MenuTool::MenuCommand1),
		FCanExecuteAction()
	);
}


void MenuTool::OnStartupModule()
{
	CommandList = MakeShareable(new FUICommandList);
	MenuToolCommands::Register();
	MapCommands();
	FToolExampleEditor::Get().AddMenuExtension
	(
		FMenuExtensionDelegate::CreateRaw(this, &MenuTool::MakeMenuEntry),
		FName("Section_1"),
		CommandList
	);
}

void MenuTool::OnShutdownModule()
{
	MenuToolCommands::Unregister();
}

void MenuTool::MakeMenuEntry(FMenuBuilder& _menuBuilder)
{
	_menuBuilder.AddMenuEntry(MenuToolCommands::Get().MenuCommand1);

	_menuBuilder.AddSubMenu(
		FText::FromString("Sub Menu"),
		FText::FromString("Example sub menu"),
		FNewMenuDelegate::CreateSP(this, &MenuTool::MakeSubMenu)
	);

	TSharedRef<SWidget> _addTagWidget = 
		SNew(SHorizontalBox)
		+ SHorizontalBox::Slot()
		.AutoWidth()
		.VAlign(VAlign_Center)
		[
			SNew(SEditableTextBox)
			.MinDesiredWidth(50)
			.Text(this, &MenuTool::GetTagToAddText)
			.OnTextCommitted(this, &MenuTool::OnTagToAddTextCommited)
		]
	+ SHorizontalBox::Slot()
		.AutoWidth()
		.Padding(5, 0, 0, 0)
		.VAlign(VAlign_Center)
		[
			SNew(SButton)
			.Text(FText::FromString("Add Tag"))
		.OnClicked(this, &MenuTool::AddTag)
		];

	_menuBuilder.AddWidget(_addTagWidget, FText::FromString(""));
}

void MenuTool::MenuCommand1()
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("Hey"));
}

void MenuTool::MakeSubMenu(FMenuBuilder& _menuBuilder)
{
	_menuBuilder.AddMenuEntry(MenuToolCommands::Get().MenuCommand2);
	_menuBuilder.AddMenuEntry(MenuToolCommands::Get().MenuCommand3);
}

FReply MenuTool::AddTag()
{
	if (TagToAdd.IsNone()) return FReply::Handled();

	const FScopedTransaction Transaction(FText::FromString("Add Tag"));
	for(FSelectionIterator it(GEditor->GetSelectedActorIterator()); it; ++it)
	{
		AActor* _actor = static_cast<AActor*>(*it);
		if(!_actor->Tags.Contains(TagToAdd))
		{
			_actor->Modify();
			_actor->Tags.Add(TagToAdd);
		}
	}
	return FReply::Handled();
}

FText MenuTool::GetTagToAddText() const
{
	return FText::FromName(TagToAdd);
}

void MenuTool::OnTagToAddTextCommited(const FText& _inText, ETextCommit::Type _commitInfo)
{
	FString _str = _inText.ToString();
	TagToAdd = FName(*_str.TrimStartAndEnd());
}

#undef LOCTEXT_NAMESPACE