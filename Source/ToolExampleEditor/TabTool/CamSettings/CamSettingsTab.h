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
	SLATE_ARGUMENT(TSharedPtr<IDetailsView>, DetailsView)
	SLATE_END_ARGS()

	void Construct(const FArguments& _inArgs);
private:
	
	void InitDetails();
	void InitDetailView();


	// for undo / redo
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;

	void OnActionOnActor(AActor* _actor);

	TAttribute<FText> cameraObjectName;
	FText GetCameraObjectName() const;
protected:
	TWeakPtr<TabTool> tool;
	ACineCameraActor* cineCamera;

	FDetailsViewArgs detailsViewArgs;
	TSharedPtr<IDetailsView> detailsView;
};

