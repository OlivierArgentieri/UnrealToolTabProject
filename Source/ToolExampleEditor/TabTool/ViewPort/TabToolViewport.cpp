#include "TabToolViewport.h"
#include "Widgets/Layout/SGridPanel.h"
#include "Widgets/Layout/SScrollBox.h"

void TabToolViewport::Construct(const FArguments& _inArgs)
{
	/*
        tool = _inArgs._Tool;
		stackLayout = FTabManager::NewLayout("Standalone_BehaviorTree_Layout_v1")
			->AddArea
			(
				FTabManager::NewPrimaryArea()->SetOrientation(Orient_Vertical)
				->Split
				(
					FTabManager::NewStack()
					->SetSizeCoefficient(0.1f)
					->AddTab("ContentBrowser", ETabState::OpenedTab)
					->SetHideTabWell(true)
				)
			);
        
		*/
	if (tool.IsValid()) {}
	FText RightContentText = FText(FText::FromString(TEXT("ttteeeeeest")));
	FColor BadgeTextColor = FColor(128, 128, 128, 255);

	TSharedRef<SWidget> DefaultNamePlate = SNew(STextBlock)
		.Text(RightContentText)
		.Visibility(EVisibility::HitTestInvisible)
		.TextStyle(FEditorStyle::Get(), "SProjectBadge.Text")
		.ColorAndOpacity(BadgeTextColor);
	ChildSlot
	[
		SNew(SScrollBox)
		+ SScrollBox::Slot()
		.VAlign(VAlign_Top)
		.Padding(5)
		[
		
			SNew(SBorder)
			.BorderBackgroundColor(FColor(255,0,0,255))
			.Padding(15.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("This is a tab example.")))
			]
		]

		+ SScrollBox::Slot()
		.Padding(5.0f)
		[	
			SNew(SGridPanel)
			.FillColumn(0, 0.5f)
			.FillColumn(1, 0.5f)

			+ SGridPanel::Slot(0,0)
			[
			        SNew(STextBlock)
			        .Text(FText::FromString(TEXT("SBorderLabel SBorder")))
			]

		        + SGridPanel::Slot(1, 0)
			.Padding(0.0f, 5.0f)
			[
				SNew(SBorder)
				[
					SNew(SSpacer)
					.Size(FVector2D(100.0f, 50.0f))
				]
			]

			// SBreadcrumbTrailLabel
			+ SGridPanel::Slot(0, 1)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("SBreadcrumbTrailLabel SBreadcrumbTrail")))
			]

			+ SGridPanel::Slot(1, 1)
			.Padding(0.0f, 5.0f)
			[
				SNew(SHorizontalBox)
				+ SHorizontalBox::Slot()
				.FillWidth(1.0f)
				[
					//SAssignNew(BreadcrumbTrail, SBreadcrumbTrail<int32>)
					SNew(STextBlock)
					.Text(FText::FromString(TEXT("This is a tab example.")))
				]

			        + SHorizontalBox::Slot()
				.AutoWidth()
				[
					SNew(SButton)
					.Text(FText::FromString(TEXT("AddBreadCrumbLabel Add")))
			            	.HAlign(HAlign_Center)
				        .VAlign(VAlign_Center)
			        	//.OnClicked(this, NULL)
				]
			]
			+ SGridPanel::Slot(1, 2)
			.HAlign(HAlign_Left)
			.Padding(0.0f, 5.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString(TEXT("This is a tab example.")))
			]
		]
	];
}