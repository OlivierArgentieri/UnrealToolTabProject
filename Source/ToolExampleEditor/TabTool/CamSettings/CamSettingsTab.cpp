#include "CamSettingsTab.h"

// target AActor
#include "CineCameraActor.h"

// global
#include "Engine/Engine.h"

// for FDetailsViewArgs
#include "Editor/UnrealEdEngine.h"
#include "IDetailsView.h"
#include "UnrealEdGlobals.h"

#define LOCTEXT_NAMESPACE "CamSettingsTab"


void CamSettingsTab::Construct(const FArguments& _inArgs)
{
	tool = _inArgs._Tool;
	
	GEngine->OnLevelActorDeleted().AddRaw(this, &CamSettingsTab::OnActionOnActor);
	GEngine->OnLevelActorAdded().AddRaw(this, &CamSettingsTab::OnActionOnActor);
	GEditor->RegisterForUndo(this);

	InitDetails();
	InitDetailView();
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
	FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, false, GUnrealEd);
	DetailsViewArgs.bShowActorLabel = false;
	//DetailsViewArgs.ObjectFilter = filter;


	detailsView = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailsViewArgs);

	detailsView->SetObject(cineCamera);

	ChildSlot
		[
			detailsView
		];
}

void CamSettingsTab::PostUndo(bool bSuccess)
{
	InitDetails();
}

void CamSettingsTab::PostRedo(bool bSuccess)
{
	InitDetails();
}


void CamSettingsTab::OnActionOnActor(AActor* _actor)
{
	InitDetails();
}
#undef LOCTEXT_NAMESPACE