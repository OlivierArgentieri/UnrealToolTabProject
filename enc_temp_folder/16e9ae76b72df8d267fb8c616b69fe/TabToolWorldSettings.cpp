#include "TabToolWorldSettings.h"

#include "Widgets/Layout/SScrollBox.h"
#include "Widgets/Input/SSpinBox.h"
#include "Components/SkyLightComponent.h"
#include "Engine/SkyLight.h"
#include "Engine/Engine.h"

#define LOCTEXT_NAMESPACE "TabToolWorldSettings"

void TabToolWorldSettings::Construct(const FArguments& _inArgs)
{
	tool = _inArgs._Tool;

	GEngine->OnLevelActorDeleted().AddRaw(this, &TabToolWorldSettings::TestCallback);
	GEngine->OnLevelActorAdded().AddRaw(this, &TabToolWorldSettings::TestCallback);
	GEngine->OnLevelActorOuterChanged().AddRaw(this, &TabToolWorldSettings::TestCallback);
	GEditor->RegisterForUndo(this);



	InitDetails();

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
					+ SHorizontalBox::Slot().FillWidth(0.5f)[SNew(STextBlock).Text(FText::FromString("Light Intensity"))]
					+ SHorizontalBox::Slot().FillWidth(0.5f)
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

void TabToolWorldSettings::TestCallback(AActor* _osef)
{
	InitDetails();
}
void TabToolWorldSettings::TestCallback(AActor* _osef, UObject* _osef2)
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
