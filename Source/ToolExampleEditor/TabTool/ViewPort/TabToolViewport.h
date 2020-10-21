#pragma once

#include "Slate/Private/Framework/Docking/SDockingTabStack.h"
#include "Templates/SharedPointer.h"
#include "ToolExampleEditor/TabTool/TabTool.h"

class TabToolViewport : public SDockTab
{
private:
	
	SLATE_BEGIN_ARGS(TabToolViewport){}
	SLATE_ARGUMENT(TWeakPtr<class TabTool>, Tool)
	SLATE_END_ARGS()

	void Construct(const FArguments& _inArgs);
	
	
protected:
	TWeakPtr<TabTool> tool;
	TSharedRef<FTabManager::FLayout> stackLayout;
};
