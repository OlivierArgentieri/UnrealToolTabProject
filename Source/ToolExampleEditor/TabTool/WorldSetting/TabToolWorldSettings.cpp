#include "TabToolWorldSettings.h"



#include "DetailsViewObjectFilter.h"
#include "UnrealEdGlobals.h"
#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Components/SkyLightComponent.h"
#include "Editor/UnrealEdEngine.h"
#include "Engine/SkyLight.h"
#include "Engine/Engine.h"
#include "PropertyEditor/Private/SDetailsView.h"
#include "Slate/Private/Widgets/Views/SListPanel.h"


class TestFilter : public FDetailsViewObjectFilter
{
public:
	virtual TArray<FDetailsViewObjectRoot> FilterObjects(const TArray<UObject*>& SourceObjects) override
	{
		TArray<FDetailsViewObjectRoot> _toReturn = TArray<FDetailsViewObjectRoot>();

		FDetailsViewObjectRoot _first = FDetailsViewObjectRoot();
		_first.Objects.Add(SourceObjects[0]);

		_toReturn.Add(_first);
		
		return _toReturn;
	}
	
};

#define LOCTEXT_NAMESPACE "TabToolWorldSettings"

void TabToolWorldSettings::Construct(const FArguments& _inArgs)
{
	tool = _inArgs._Tool;

	GEngine->OnLevelActorDeleted().AddRaw(this, &TabToolWorldSettings::TestCallback);
	GEngine->OnLevelActorAdded().AddRaw(this, &TabToolWorldSettings::TestCallback);
	GEditor->RegisterForUndo(this);

	// setup the detail view settings
	FDetailsViewArgs DetailsViewArgs(false, false, true, FDetailsViewArgs::HideNameArea, false, GUnrealEd);
	DetailsViewArgs.bShowActorLabel = false;
	TSharedRef<IDetailsView> WorldSettingsView = FModuleManager::LoadModuleChecked<FPropertyEditorModule>("PropertyEditor").CreateDetailView(DetailsViewArgs);


	
	InitDetails();
	WorldSettingsView->SetObject(sceneSkyLight);
	//TSharedPtr<TestFilter> filter = TSharedPtr<TestFilter>();
	//filter.Get()->FilterObjects(USkyLightComponent);
	//WorldSettingsView->SetObjectFilter(filter);
	skyLightIntensity.Bind(this, &TabToolWorldSettings::GetSceneLightIntensity);
	skyLightExist.Bind(this, &TabToolWorldSettings::GetSceneLightExist);
	
	if (tool.IsValid())
	{
		// action from tool object
	}

	ChildSlot
		[
			SNew(SScrollBox)
			+ SScrollBox::Slot()
			.VAlign(VAlign_Top)
			.Padding(5)
			[
				SNew(SBorder)
				.BorderBackgroundColor(FColor(192, 192, 192, 255))
				.Padding(15.0f)
				[
					SNew(SHorizontalBox)
					+ SHorizontalBox::Slot().AutoWidth().FillWidth(0.5f)[SNew(STextBlock).Text(FText::FromString("Light Intensity"))]
					+ SHorizontalBox::Slot().AutoWidth().FillWidth(0.5f)
					[
						SNew(SSpinBox<float>)
						.Value(skyLightIntensity)
						.Tag("LightIntensity")
						.OnValueChanged(this, &TabToolWorldSettings::OnIntensityChanged)
						.MinValue(-20.0f).MaxValue(20.0f).Value(0.5f)
						.IsEnabled(skyLightExist)
					]
				]
			]
			+ SScrollBox::Slot()
			.VAlign(VAlign_Top)
			.Padding(5)
			[
				SNew(SButton)
				.OnClicked(this, &TabToolWorldSettings::HitButton)
				[
					SNew(STextBlock)
					.Text(FText::FromString("test"))
					.ToolTipText(LOCTEXT("OSEF", "Click !"))
				]
			]
			+ SScrollBox::Slot()
				.VAlign(VAlign_Top)
				.Padding(5)

				[
					SNew(SBorder)
					.BorderBackgroundColor(FColor(192, 192, 192, 255))
					.Padding(15.0f)
					[
						SNew(SVerticalBox) // title PostProcess
						+ SVerticalBox::Slot()[SNew(STextBlock).Text(FText::FromString("Post Process"))]
						+ SVerticalBox::Slot()
						.AutoHeight()
						[
							SNew(SBorder) 
							.BorderBackgroundColor(FColor(192, 192, 192, 255))
							.Padding(15.0f)
							[
								
								SNew(SBox)
								//.HAlign(HAlign_Left)
								[
									SNew(SSplitter)
									.MinimumSlotHeight(2)
									.Orientation(Orient_Horizontal)
									.PhysicalSplitterHandleSize(1)
									.HitDetectionSplitterHandleSize(5.0f)
									+ SSplitter::Slot().Value(0.672f)
									[
										SNew(STextBlock)
										.Text(FText::FromString("test"))
										.ToolTipText(LOCTEXT("OSEF", "Click !"))
									]
									+ SSplitter::Slot().Value(0.672f)
									[

										SNew(SSpinBox<float>)
										.Value(skyLightIntensity)
										.Tag("LightIntensity")
										.OnValueChanged(this, &TabToolWorldSettings::OnIntensityChanged)
										.MinValue(0).MaxValue(50000.0f).Value(0.5f)
										.IsEnabled(skyLightExist)

									]

								]
							]
							
						]
						
					]

					/*
					SNew(SVerticalBox)
					+ SVerticalBox::Slot()
					.HAlign(HAlign_Left)
					.VAlign(VAlign_Center)
					[
					//	SNew(SListPanel)
					//	.NumDesiredItems(7)
						SNew(STextBlock)
						.Text(FText::FromString("test"))
						.ToolTipText(LOCTEXT("OSEF", "Click !"))
					]*/
				]
				 +SScrollBox::Slot()
				.VAlign(VAlign_Top)
				.Padding(5)
				 [
					WorldSettingsView
				 ]
		];
}


void TabToolWorldSettings::InitDetails()
{
	sceneSkyLight = nullptr;
	auto world = GEditor->GetEditorWorldContext().World();
	
	for (AActor* _actor : world->GetCurrentLevel()->Actors)
	{
		if (!_actor) continue;
		
		if (_actor->GetName() == FString("SkyLight_1"))
			sceneSkyLight = Cast<ASkyLight>(_actor);
	}
}

void TabToolWorldSettings::OnIntensityChanged(float NewValue)
{
	if (!sceneSkyLight) return;
	
	sceneSkyLight->GetLightComponent()->Intensity = NewValue;
}

FReply TabToolWorldSettings::HitButton()
{
	FMessageDialog::Open(EAppMsgType::Ok, FText::FromString("hey"));

	return FReply::Handled();
}

void TabToolWorldSettings::TestCallback(AActor* _actor)
{
	InitDetails();
}

float TabToolWorldSettings::GetSceneLightIntensity() const
{
	if (!sceneSkyLight) return 0;
	
	return sceneSkyLight->GetLightComponent()->Intensity;
}

bool TabToolWorldSettings::GetSceneLightExist() const
{
	return sceneSkyLight != nullptr;
}



void TabToolWorldSettings::PostUndo(bool bSuccess)
{
	InitDetails();
}

void TabToolWorldSettings::PostRedo(bool bSuccess)
{
	InitDetails();
}
#undef LOCTEXT_NAMESPACE
