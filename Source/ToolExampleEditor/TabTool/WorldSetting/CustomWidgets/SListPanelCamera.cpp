#include "SListPanelCamera.h"

#include "CoreMinimal.h"
#include "DetailCategoryBuilder.h"
#include "DetailLayoutBuilder.h"
#include "DetailWidgetRow.h"

#define LOCTEXT_NAMESPACE "SListPanelCamera"

void SListPanelCamera::CustomizeDetails(IDetailLayoutBuilder& DetailBuilder)
{
	IDetailCategoryBuilder& DetailsCategory = DetailBuilder.EditCategory("Details", FText::GetEmpty(), ECategoryPriority::Important);
	static const FText RowText = LOCTEXT("Category_Details", "Details");
	DetailsCategory.AddCustomRow(RowText)
		.WholeRowContent()
		[
			SNew(SVerticalBox)

			+ SVerticalBox::Slot()
			.AutoHeight()
			.VAlign(VAlign_Center)
			.Padding(4.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString("test"))
				.ToolTipText(LOCTEXT("OSEF", "Click !"))
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			.VAlign(VAlign_Center)
			.Padding(4.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString("test"))
				.ToolTipText(LOCTEXT("OSEF", "Click !"))
			]

			+ SVerticalBox::Slot()
			.AutoHeight()
			.VAlign(VAlign_Center)
			.Padding(4.0f)
			[
				SNew(STextBlock)
				.Text(FText::FromString("test"))
				.ToolTipText(LOCTEXT("OSEF", "Click !"))
			]
		];
}

#undef LOCTEXT_NAMESPACE 
