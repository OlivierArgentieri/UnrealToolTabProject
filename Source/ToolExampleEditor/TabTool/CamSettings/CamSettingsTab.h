#pragma once
#include "EditorModeRegistry.h"
#include "Templates/SharedPointer.h"
#include "Dialogs/CustomDialog.h"
#include "Engine/Engine.h"

class ACineCameraActor;
class CamSettingsTab : public SCompoundWidget, FEditorUndoClient
{

private:
	SLATE_BEGIN_ARGS(CamSettingsTab) {}
	SLATE_ARGUMENT(TWeakPtr<class TabTool>, Tool)
	SLATE_ARGUMENT(ACineCameraActor*, CineCamera)
	//SLATE_ARGUMENT(TSharedRef<IDetailsView>, DetailsView)
	SLATE_END_ARGS()

	void Construct(const FArguments& _inArgs);
private:
	
	void InitDetails();
	void InitDetailView();


	// for undo / redo
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;

	void OnActionOnActor(AActor* _actor);
protected:
	TWeakPtr<TabTool> tool;
	ACineCameraActor* cineCamera;

	FDetailsViewArgs _detailsViewArgs;
	//TSharedRef<IDetailsView> detailsView;
};

