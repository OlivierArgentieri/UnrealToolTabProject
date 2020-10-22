#pragma once

#include "EditorModeRegistry.h"
#include "Templates/SharedPointer.h"
#include "Dialogs/CustomDialog.h"
 #include "Engine/Engine.h"

class ASkyLight;
class TabToolWorldSettings : public SCompoundWidget, FEditorUndoClient
{
private:
	SLATE_BEGIN_ARGS(TabToolWorldSettings) {}
	SLATE_ARGUMENT(TWeakPtr<class TabTool>, Tool)
	SLATE_ARGUMENT(ASkyLight*, sceneSkyLight)
	SLATE_END_ARGS()

	void Construct(const FArguments& _inArgs);
	void InitDetails();
	
	void OnIntensityChanged(float NewValue);

private:
	// for undo / redo
	virtual void PostUndo(bool bSuccess) override;
	virtual void PostRedo(bool bSuccess) override;
	
protected:
	TWeakPtr<TabTool> tool;
	FOnClicked onClicked;

	FReply HitButton();
	void TestCallback(AActor* _actor);


	// Details test
	TAttribute<float> skyLightIntensity;
	TAttribute<bool> skyLightExist;
	
	float GetSceneLightIntensity() const;
	bool GetSceneLightExist() const;

	ASkyLight* sceneSkyLight;


	// test Slist
	//SListPanel panel;
	/**	 */
	FDetailsViewArgs detailsVeiwArgs;
};