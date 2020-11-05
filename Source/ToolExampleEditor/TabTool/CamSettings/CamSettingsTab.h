#pragma once
#include "EditorModeRegistry.h"
#include "Templates/SharedPointer.h"
#include "Dialogs/CustomDialog.h"
#include "Engine/Engine.h"
#include "Hook/CamSettingHook.h"
#include <ToolExampleEditor\TabTool\CamSettings\Hook\CamSettingHook.h>

class UCamSettingTabFilterObject;
class ACineCameraActor;
class IPropertyChangeListener;
class CamSettingsTab : public SCompoundWidget, FEditorUndoClient, FNotifyHook
{

private:
	SLATE_BEGIN_ARGS(CamSettingsTab) {}
	SLATE_ARGUMENT(TWeakPtr<class TabTool>, Tool)
	SLATE_ARGUMENT(ACineCameraActor*, CineCamera)
	SLATE_ARGUMENT(TSharedPtr<IDetailsView>, DetailsView)
	SLATE_ARGUMENT(UCamSettingTabFilterObject*, Wrapper)
	SLATE_END_ARGS()

	void Construct(const FArguments& _inArgs);
	FReply OnPress();
	~CamSettingsTab();
	
private:
	
	void InitDetails();
	void InitDetailView();


	// for undo / redo
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;

	void OnActionOnActor(AActor* _actor);

	// store delegate to delete
	FDelegateHandle actorAddedDelegate;
	FDelegateHandle actorDeletedDelegate;
	
	TAttribute<FText> cameraObjectName;
	FText GetCameraObjectName() const;

	virtual void NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged) override;
	void OnEditPropertyMainDetailsView(const TArray<UObject*>&, const IPropertyHandle&);
	UCamSettingTabFilterObject* wrapper;
	
protected:
	TWeakPtr<TabTool> tool;
	ACineCameraActor* cineCamera;

	FDetailsViewArgs detailsViewArgs;
	TSharedPtr<IDetailsView> detailsView;
	TSharedPtr<IPropertyChangeListener> changedListener;
};