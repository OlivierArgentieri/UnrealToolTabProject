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

	actorDeletedDelegate = GEngine->OnLevelActorDeleted().AddRaw(this, &CamSettingsTab::OnActionOnActor);
	actorAddedDelegate = GEngine->OnLevelActorAdded().AddRaw(this, &CamSettingsTab::OnActionOnActor);
	GEditor->RegisterForUndo(this);
	
	cameraObjectName.Bind(this, &CamSettingsTab::GetCameraObjectName);
	
	TSharedPtr<CamSettingTabFilter> _filter(new CamSettingTabFilter);
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

	FProperty* test = cineCamera->GetCameraComponent()->GetClass()->FindPropertyByName("PostProcessSettings");

	if(test)
	{
		void* addr = test->ContainerPtrToValuePtr<void>(cineCamera->GetCameraComponent());
		//void* Myaddr = PropertyThatChanged->ContainerPtrToValuePtr<void>(cineCamera->GetCameraComponent());

		if(UStructProperty* structProp = Cast<UStructProperty>(test))
		{
			UScriptStruct* scriptStruct = structProp->Struct;


			
			FProperty* boolChildProp = scriptStruct->FindPropertyByName("bOverride_BloomIntensity");
			if (UBoolProperty* childBoolProp = Cast<UBoolProperty>(boolChildProp))
			{
				childBoolProp->SetPropertyValue(addr, true);
			}
			
			FProperty* childProp = scriptStruct->FindPropertyByName("BloomIntensity");

			if(UFloatProperty* childFloatProp = Cast<UFloatProperty>(childProp))
			{
				float oldValue = childFloatProp->GetFloatingPointPropertyValue(addr);

				//(UFloatProperty * childMyProperty = Cast<UFloatProperty>(childProp)
				float my_newValue = childFloatProp->GetFloatingPointPropertyValue(addr);

				childFloatProp->SetFloatingPointPropertyValue(addr, 8);

				
			}
			
			
		}
	}
	
	/*PropertyThatChanged->GetClass()->
	for (TFieldIterator<FProperty> PropIt(PropertyThatChanged->Owner.GetOwnerClass()); PropIt; ++PropIt)
	{
		if(PropIt->IsA(UFloatProperty::StaticClass()))
		{
			UFloatProperty* t = CastChecked<UFloatProperty>(PropertyThatChanged);
			test = t->GetFloatingPointPropertyValue(t->ContainerPtrToValuePtr<float>(PropertyThatChanged));

			auto sss = t;
		}
	}*/
	//PropertyChangedEvent.MemberProperty.
	//auto c = Cast<UCamSettingTabFilterObject>(f);
	//if(PropertyThatChanged->GetNameCPP() == "BloomIntensity")
	//	cineCamera->GetCameraComponent()->PostProcessSettings.BloomIntensity = *Cast<float>(PropertyChangedEvent.MemberProperty);
}
#undef LOCTEXT_NAMESPACE