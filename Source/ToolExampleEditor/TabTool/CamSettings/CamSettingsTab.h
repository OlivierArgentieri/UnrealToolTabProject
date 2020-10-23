#pragma once
#include "Engine/Engine.h"
#include "Templates/SharedPointer.h"

class ACineCameraActor;
class CamSettingsTab : public SCompoundWidget, FEditorUndoClient
{

private:
	SLATE_BEGIN_ARGS(CamSettingsTab) {}
	SLATE_ARGUMENT(TWeakPtr<class TabTool>, Tool)
	SLATE_ARGUMENT(ACineCameraActor*, CineCamera)
	SLATE_END_ARGS()

private:
	void Construct(const FArguments& _inArgs);
	void InitDetails();
	void InitDetailView();


	// for undo / redo
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;

	void OnActionOnActor(AActor* _actor);
private:
	TWeakPtr<TabTool> tool;
	ACineCameraActor* cineCamera;
	TSharedRef<IDetailsView> detailsView;
};

