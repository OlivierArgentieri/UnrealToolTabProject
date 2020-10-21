#pragma once

#include "Templates/SharedPointer.h"
#include "Dialogs/CustomDialog.h"

class TabToolWorldSettings : public SCompoundWidget
{
private:
	SLATE_BEGIN_ARGS(TabToolWorldSettings) {}
	SLATE_ARGUMENT(TWeakPtr<class TabTool>, Tool)
	SLATE_END_ARGS()

	void Construct(const FArguments& _inArgs);
	void OnIntensityChanged(float NewValue);


protected:
	TWeakPtr<TabTool> tool;
	FOnClicked onClicked;

	FReply HitButton();
};
