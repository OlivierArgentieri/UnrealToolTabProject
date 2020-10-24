#include "CamSettingsTab.h"
#include "PropertyEditor/Private/SDetailsView.h"
// target AActor
#include "CineCameraActor.h"

// global
#include "Engine/Engine.h"

// for FDetailsViewArgs
#include "Editor/UnrealEdEngine.h"
#include "IDetailsView.h"
#include "UnrealEdGlobals.h"
#include "Filter/CamSettingTabFilter.h"
#include "Widgets/Layout/SScrollBox.h"

#define LOCTEXT_NAMESPACE "CamSettingsTab"


void CamSettingsTab::Construct(const FArguments& _inArgs)
{
	tool = _inArgs._Tool;

	GEngine->OnLevelActorDeleted().AddRaw(this, &CamSettingsTab::OnActionOnActor);
	GEngine->OnLevelActorAdded().AddRaw(this, &CamSettingsTab::OnActionOnActor);
	GEditor->RegisterForUndo(this);
	cameraObjectName.Bind(this, &CamSettingsTab::GetCameraObjectName);
	
	TSharedPtr<CamSettingTabFilter> _filter(new CamSettingTabFilter);
	detailsViewArgs = FDetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, false, GUnrealEd);
	detailsViewArgs.bShowActorLabel = false;
	detailsViewArgs.ObjectFilter = _filter;
	
	InitDetails();
	InitDetailView();
	
	detailsView = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(detailsViewArgs);

	detailsView->HideFilterArea(true);
	
	ChildSlot
	[
		SNew(SVerticalBox)
		+ SVerticalBox::Slot().AutoHeight().FillHeight(0.162f)[SNew(STextBlock).Text(cameraObjectName)]
		+ SVerticalBox::Slot().AutoHeight()
		[
			detailsView.ToSharedRef()
		]
		
	];
}

void CamSettingsTab::InitDetails()
{
	cineCamera = nullptr;
	auto _world = GEditor->GetEditorWorldContext().World();


	for (AActor* _actor : _world->GetCurrentLevel()->Actors)
	{
		if (!_actor) continue;

		cineCamera = Cast<ACineCameraActor>(_actor);
		if(cineCamera != nullptr)
			return;
	}

}


void CamSettingsTab::InitDetailView()
{
	if (!detailsView) return;
	detailsView->SetEnabled(false);

	if (!cineCamera) return;
	detailsView->SetObject(cineCamera);
	detailsView->SetEnabled(true);
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

FText CamSettingsTab::GetCameraObjectName() const
{

	if (cineCamera)
		return FText::AsCultureInvariant(cineCamera->GetName());
	return FText::FromString("No Camera found");
	
}
#undef LOCTEXT_NAMESPACE
