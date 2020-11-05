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
#include "IPropertyChangeListener.h"
#include "DetailLayoutBuilder.h"
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
	detailsViewArgs = FDetailsViewArgs(true, false, true, FDetailsViewArgs::HideNameArea, false, GUnrealEd);
	//detailsViewArgs.NotifyHook
	detailsViewArgs.bShowActorLabel = false;
	detailsViewArgs.ObjectFilter = _filter;
	detailsViewArgs.NotifyHook = this;

	FPropertyEditorModule& PropertyEditorModule = FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor");
	PropertyEditorModule.NotifyCustomizationModuleChanged();

	
	
	
	InitDetails();
	InitDetailView();
	detailsView.Get()->SetObjectFilter(_filter);
	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		.VAlign(VAlign_Top)
		.Padding(5)
		[
			SNew(SButton)
			.OnClicked(this, &CamSettingsTab::OnPress)
			[
				SNew(STextBlock)
				.Text(FText::FromString("test"))
				.ToolTipText(LOCTEXT("test refresh", "Click !"))
			]
		]
		+ SScrollBox::Slot()
		.VAlign(VAlign_Top)
		.Padding(5)[

			detailsView.ToSharedRef()
		]
	];
}


FReply CamSettingsTab::OnPress()
{
	FModuleManager::GetModuleChecked<FPropertyEditorModule>("PropertyEditor").NotifyCustomizationModuleChanged();
	// detailsView-> see : https://answers.unrealengine.com/questions/265765/how-to-update-customized-details-panel.html
	//detailsView.ad
	InitDetails();
	InitDetailView();
	//FProperty* _postProcessProperty = cineCamera->GetCameraComponent()->GetClass()->FindPropertyByName("PostProcessSettings");
	//void* _postProcessStructAddr = _postProcessProperty->ContainerPtrToValuePtr<void>(cineCamera->GetCameraComponent());
	//void* _wrapperStructAddr = _postProcessProperty->ContainerPtrToValuePtr<void>(wrapper);

	//FStructProperty* _postprocessPropertyCamera = Cast<FStructProperty>(_postProcessProperty);
	//FStructProperty* _postprocessPropertyWrapper = Cast<FStructProperty>(_wrapperStructAddr);
	//
	//UScriptStruct* _postProcessStructWrapper = _postprocessPropertyWrapper->Struct;
	//UScriptStruct* _postProcessStructCamera = _postprocessPropertyCamera->Struct;
	UE_LOG(LogTemp, Warning, TEXT("Hey"));
	return FReply::Handled();
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
		changedListener = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor").CreatePropertyChangeListener();
		changedListener->GetOnPropertyChangedDelegate().AddRaw(this, &CamSettingsTab::OnEditPropertyMainDetailsView);
		//detailsView->HideFilterArea(true);
		//detailsView->
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
		FProperty* _postProcessProperty = cineCamera->GetCameraComponent()->GetClass()->FindPropertyByName("PostProcessSettings");
		void* _postProcessStructAddr = _postProcessProperty->ContainerPtrToValuePtr<void>(cineCamera->GetCameraComponent());


		void* _wrapperStructAddr = PropertyChangedEvent.MemberProperty->ContainerPtrToValuePtr<void>(wrapper);

		FStructProperty* _postProcessPropertyWrapper = Cast<FStructProperty>(PropertyChangedEvent.MemberProperty);
		FStructProperty* _postprocessPropertyCamera = Cast<FStructProperty>(_postProcessProperty);

		if (_postProcessPropertyWrapper && _postprocessPropertyCamera)
		{
			UScriptStruct* _postProcessStructWrapper = _postProcessPropertyWrapper->Struct;
			UScriptStruct* _postProcessStructCamera = _postprocessPropertyCamera->Struct;


			// force Activation of property
			FBoolProperty* _bOverride_PropertyWrapper = Cast<FBoolProperty>(_postProcessStructWrapper->FindPropertyByName(FName("bOverride_" + PropertyThatChanged->GetName())));
			FBoolProperty* _bOverride_PropertyCamera = Cast<FBoolProperty>(_postProcessStructCamera->FindPropertyByName(FName("bOverride_" + PropertyThatChanged->GetName())));
			if (_bOverride_PropertyWrapper && _bOverride_PropertyCamera)
			{
				bool _propertyIsActivated = _bOverride_PropertyCamera->GetPropertyValue_InContainer(_postProcessStructAddr);
				bool _editedValue = _bOverride_PropertyWrapper->GetPropertyValue_InContainer(_wrapperStructAddr);

			    if(_propertyIsActivated != _editedValue) 
			    {
				_bOverride_PropertyCamera->SetPropertyValue_InContainer(_postProcessStructAddr, _editedValue);
			        return;
			    }
			}

			FBoolProperty* _b_PropertyWrapper = Cast<FBoolProperty>(_postProcessStructWrapper->FindPropertyByName(PropertyThatChanged->GetFName()));
			FBoolProperty* _b_PropertyCamera = Cast<FBoolProperty>(_postProcessStructCamera->FindPropertyByName(PropertyThatChanged->GetFName()));
			if (_b_PropertyWrapper && _b_PropertyCamera)
			{
				bool _editedValue = _b_PropertyWrapper->GetPropertyValue_InContainer(_wrapperStructAddr);
				_b_PropertyCamera->SetPropertyValue_InContainer(_postProcessStructAddr, _editedValue);
				return;
			}

			FFloatProperty* _f_PropertyWrapper = Cast<FFloatProperty>(_postProcessStructWrapper->FindPropertyByName(PropertyThatChanged->GetFName()));
			FFloatProperty* _f_PropertyCamera = Cast<FFloatProperty>(_postProcessStructCamera->FindPropertyByName(PropertyThatChanged->GetFName()));
			if (_f_PropertyWrapper && _f_PropertyCamera)
			{
				float _editedValue = _f_PropertyWrapper->GetPropertyValue_InContainer(_wrapperStructAddr);
				_f_PropertyCamera->SetPropertyValue_InContainer(_postProcessStructAddr, _editedValue);
				return;
			}
		}
	}

  /*
	if (PropertyChangedEvent.Property && PropertyChangedEvent.MemberProperty->GetFName() == GET_MEMBER_NAME_CHECKED(UCameraComponent, PostProcessSettings))
	{
		FProperty* _postProcessProperty = cineCamera->GetCameraComponent()->GetClass()->FindPropertyByName("PostProcessSettings");

		void* _structAddr = _postProcessProperty->ContainerPtrToValuePtr<void>(cineCamera->GetCameraComponent());

		if (_postProcessProperty)
		{
			FStructProperty* _postprocessProperty = Cast<FStructProperty>(_postProcessProperty);

			UScriptStruct* _postProcessStruct = _postprocessProperty->Struct;
			FBoolProperty* _b_bloomIntensityProperty = Cast<FBoolProperty>(_postProcessStruct->FindPropertyByName(GET_MEMBER_NAME_CHECKED(FPostProcessSettings, bOverride_BloomIntensity)));
			if (_b_bloomIntensityProperty)
			{
				
				_b_bloomIntensityProperty->SetPropertyValue_InContainer(_structAddr, true);
				float _second = 1; 
				return;
			}
		}
	}*/



	
}

void CamSettingsTab::OnEditPropertyMainDetailsView(const TArray<UObject*>& _object, const class IPropertyHandle& _handleProperty)
{
	UE_LOG(LogTemp, Warning, TEXT("Hey"));

	
	
}
#undef LOCTEXT_NAMESPACE