#include "CamSettingsTab.h"

// target AActor
#include "CineCameraActor.h"

// global
#include "Engine/Engine.h"

// for FDetailsViewArgs
#include "Editor/UnrealEdEngine.h"
#include "IDetailsView.h"
#include "UnrealEdGlobals.h"
#include "Filter/CamSettingTabFilter.h"

#define LOCTEXT_NAMESPACE "CamSettingsTab"


void CamSettingsTab::Construct(const FArguments& _inArgs)
{
	//tool = _inArgs._Tool;
	
	//GEngine->OnLevelActorDeleted().AddRaw(this, &CamSettingsTab::OnActionOnActor);
//	GEngine->OnLevelActorAdded().AddRaw(this, &CamSettingsTab::OnActionOnActor);
	//GEditor->RegisterForUndo(this);

	//InitDetails();
	//InitDetailView();
}

void CamSettingsTab::InitDetails()
{
	cineCamera = nullptr;
	auto _world = GEditor->GetEditorWorldContext().World();

	
	for (AActor* _actor : _world->GetCurrentLevel()->Actors)
	{
		if (!_actor) continue;
		
		cineCamera = Cast<ACineCameraActor>(_actor);
		
		if (cineCamera != nullptr) // get first
			return;
	}
}


void CamSettingsTab::InitDetailView()
{
	//TSharedPtr<CamSettingTabFilter> _filter(new CamSettingTabFilter);
	FDetailsViewArgs _detailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, false, GUnrealEd);
	_detailsViewArgs.bShowActorLabel = false;
	//_detailsViewArgs.ObjectFilter = _filter;


	detailsView = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(_detailsViewArgs);

	detailsView->SetObject(cineCamera);
	detailsView->HideFilterArea(true);

	ChildSlot
	[
		detailsView
	];
}

void CamSettingsTab::PostUndo(bool bSuccess)
{
	InitDetails();
	InitDetailView();
}

void CamSettingsTab::PostRedo(bool bSuccess)
{
	InitDetails();
	InitDetailView();
}


void CamSettingsTab::OnActionOnActor(AActor* _actor)
{
	InitDetails();
	InitDetailView();
}
#undef LOCTEXT_NAMESPACE