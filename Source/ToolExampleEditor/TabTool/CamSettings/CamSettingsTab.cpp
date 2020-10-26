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
#include "Camera/CameraComponent.h"
#include "Filter/CamSettingTabFilter.h"
#include "Filter/CamSettingTabFilterObject.h"
#include "Widgets/Layout/SScrollBox.h"
#include "UObject/UObjectBase.h"
#define LOCTEXT_NAMESPACE "CamSettingsTab"


void CamSettingsTab::Construct(const FArguments& _inArgs)
{
	tool = _inArgs._Tool;
	wrapper = NewObject<UCamSettingTabFilterObject>();

	actorDeletedDelegate = GEngine->OnLevelActorDeleted().AddRaw(this, &CamSettingsTab::OnActionOnActor);
	actorDeletedDelegate = GEngine->OnLevelActorDeleted().AddRaw(this, &CamSettingsTab::OnActionOnActor);
	actorAddedDelegate = GEngine->OnLevelActorAdded().AddRaw(this, &CamSettingsTab::OnActionOnActor);
	GEditor->RegisterForUndo(this);
	
	cameraObjectName.Bind(this, &CamSettingsTab::GetCameraObjectName);
	
	TSharedPtr<CamSettingTabFilter> _filter(new CamSettingTabFilter);
	_filter->SetWrapper(wrapper);
	detailsViewArgs = FDetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, false, GUnrealEd);
	//detailsViewArgs.NotifyHook
	detailsViewArgs.bShowActorLabel = false;
	detailsViewArgs.ObjectFilter = _filter;
	detailsViewArgs.NotifyHook = this;

	
	InitDetails();
	InitDetailView();
	detailsView.Get()->SetObjectFilter(_filter);
	ChildSlot
	[
		detailsView.ToSharedRef()
	];
}

CamSettingsTab::~CamSettingsTab()
{
	GEngine->OnLevelActorDeleted().Remove(actorDeletedDelegate);
	GEngine->OnLevelActorAdded().Remove(actorAddedDelegate);
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
	if (!detailsView)
	{
		detailsView = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(detailsViewArgs);
		detailsView->HideFilterArea(true);
		
	}

	detailsView->SetEnabled(cineCamera);
	if (!cineCamera) return;
	detailsView->SetObject(cineCamera, true);
	
	//detailsView->SetEnabled(true);
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

void CamSettingsTab::NotifyPostChange(const FPropertyChangedEvent& PropertyChangedEvent, FProperty* PropertyThatChanged)
{

	if (!cineCamera || !PropertyThatChanged) return;
	/**/
	if(PropertyChangedEvent.Property && PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UCameraComponent, PostProcessSettings))
	{
		
		void* _structAddr = PropertyChangedEvent.MemberProperty->ContainerPtrToValuePtr<void>(wrapper);

		FStructProperty* _postprocessProperty = Cast<FStructProperty>(PropertyChangedEvent.MemberProperty);

		if (_postprocessProperty)
		{
			UScriptStruct* _postProcessStruct = _postprocessProperty->Struct;
			FBoolProperty* _b_bloomIntensityProperty = Cast<FBoolProperty>(_postProcessStruct->FindPropertyByName(GET_MEMBER_NAME_CHECKED(FPostProcessSettings, bOverride_BloomIntensity)));
			if (_b_bloomIntensityProperty)
			{
				bool _test = _b_bloomIntensityProperty->GetPropertyValue_InContainer(_structAddr);

				bool _second = _test; // for beakpoint 
			//	_b_bloomIntensityProperty->SetPropertyValue(_structAddr, true);
			}
		}
	}

  /*

	if (PropertyChangedEvent.Property && PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UCameraComponent, PostProcessSettings))
	{

		void* _structAddr = PropertyChangedEvent.MemberProperty->ContainerPtrToValuePtr<void>(cineCamera);

		FStructProperty* _postprocessProperty = Cast<FStructProperty>(PropertyChangedEvent.MemberProperty);

		if (_postprocessProperty)
		{
			UScriptStruct* _postProcessStruct = _postprocessProperty->Struct;
			FBoolProperty* _b_bloomIntensityProperty = Cast<FBoolProperty>(_postProcessStruct->FindPropertyByName(GET_MEMBER_NAME_CHECKED(FPostProcessSettings, bOverride_BloomIntensity)));
			if (_b_bloomIntensityProperty)
			{
				bool _test = _b_bloomIntensityProperty->GetPropertyValue_InContainer(_structAddr);
				_b_bloomIntensityProperty->SetPropertyValue_InContainer(_structAddr, true);
				bool _second = _test; // for beakpoint 
			//	_b_bloomIntensityProperty->SetPropertyValue(_structAddr, true);
			}
		}
	}*/



	
}
#undef LOCTEXT_NAMESPACE