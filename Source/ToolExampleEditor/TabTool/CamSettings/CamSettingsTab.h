#pragma once
#include "Engine/Engine.h"
#include "Templates/SharedPointer.h"
class CamSettingsTab : public SCompoundWidget, FEditorUndoClient
{

	SLATE_BEGIN_ARGS(CamSettingsTab) {}
	SLATE_ARGUMENT(TWeakPtr<class TabTool>, Tool)
    SLATE_END_ARGS()

private:
	void Construct(const FArguments& _inArgs);
	void InitDetails();

	void OnIntensityChanged(float NewValue);

	// for undo / redo
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;

protected:
	TWeakPtr<TabTool> tool;
	FOnClicked onClicked;

	FReply HitButton();
};

