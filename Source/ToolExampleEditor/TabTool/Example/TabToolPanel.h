#pragma once

#include "Templates/SharedPointer.h"
#include "Dialogs/CustomDialog.h"
class TabToolPanel : public SCompoundWidget
{
	SLATE_BEGIN_ARGS(TabToolPanel){}
	SLATE_ARGUMENT(TWeakPtr<class TabTool>, Tool)
	SLATE_END_ARGS()

	void Construct(const FArguments& _inArgs);

protected:
	TWeakPtr<TabTool> tool;
};